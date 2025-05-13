#include "SailClothComponent.h"
#include "SailClothSimShaders.h"
#include "ProceduralMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "RHICommandList.h"

#define GRID_SIZE 16

USailClothComponent::USailClothComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USailClothComponent::BeginPlay()
{
    Super::BeginPlay();

    // Initialize GPU Buffers
    FSailClothSimShaders::Initialize(
        GRHICommandList.GetImmediateCommandList(),
        SimCtx,
        GRID_SIZE, GRID_SIZE
    );

    // Create and Register Procedural Mesh Component
    ProcMesh = NewObject<UProceduralMeshComponent>(GetOwner());
    ProcMesh->RegisterComponent();
    ProcMesh->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

    // Generate initial mesh grid
    CreateInitialMesh(GRID_SIZE, GRID_SIZE);
}

void USailClothComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector3f Wind(500.0f, 0.0f, 0.0f);
    float AirDensity = 1.225f;
    float Compliance = 0.0001f;
    float StretchStiffness = 1.0f;
    float BendStiffness = 0.5f;

    // Dispatch Simulation
    FSailClothSimShaders::Simulate(
        GRHICommandList.GetImmediateCommandList(),
        SimCtx,
        DeltaTime,
        Wind,
        AirDensity,
        Compliance,
        StretchStiffness,
        BendStiffness
    );

    // Readback and Update Mesh
    ReadbackAndUpdateMesh();
}

void USailClothComponent::ReadbackAndUpdateMesh()
{
    const uint32 NumBytes = SimCtx.NumParticles * sizeof(FParticleGPU);

    // Lock the GPU buffer and retrieve data
    void* DataPtr = ParticleReadback.Lock(NumBytes);
    if (!DataPtr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to lock ParticleReadback buffer"));
        return;
    }

    // Copy data to CPU-side buffer
    FMemory::Memcpy(ParticleData.GetData(), DataPtr, NumBytes);

    // Unlock the buffer to allow the GPU to reuse it
    ParticleReadback.Unlock();

    // Update the mesh asynchronously to avoid blocking the game thread
    AsyncTask(ENamedThreads::GameThread, [this]()
        {
            if (!ProcMesh) return;

            TArray<FVector> UpdatedVertices;
            UpdatedVertices.SetNum(SimCtx.NumParticles);

            for (int32 i = 0; i < SimCtx.NumParticles; ++i)
            {
                UpdatedVertices[i] = (FVector)ParticleData[i].Position;
            }

            ProcMesh->UpdateMeshSection(
                0,
                UpdatedVertices,
                TArray<FVector>(),  // Normals (optional)
                TArray<FVector2D>(), // UVs (optional)
                TArray<FColor>(),   // Colors (optional)
                TArray<FProcMeshTangent>() // Tangents (optional)
            );

            VisualizeConstraints();
        });
}

void USailClothComponent::CreateInitialMesh(int32 GridWidth, int32 GridHeight)
{
    TArray<FVector> Vertices;
    TArray<int32> Triangles;

    float Spacing = 10.0f;
    Vertices.SetNum(GridWidth * GridHeight);

    for (int32 y = 0; y < GridHeight; ++y)
    {
        for (int32 x = 0; x < GridWidth; ++x)
        {
            int32 Index = y * GridWidth + x;
            Vertices[Index] = FVector(x * Spacing, y * Spacing, 0);
        }
    }

    for (int32 y = 0; y < GridHeight - 1; ++y)
    {
        for (int32 x = 0; x < GridWidth - 1; ++x)
        {
            int32 i0 = y * GridWidth + x;
            int32 i1 = i0 + 1;
            int32 i2 = i0 + GridWidth;
            int32 i3 = i2 + 1;

            Triangles.Add(i0); Triangles.Add(i2); Triangles.Add(i3);
            Triangles.Add(i0); Triangles.Add(i3); Triangles.Add(i1);
        }
    }

    ProcMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), false);
}

void USailClothComponent::VisualizeConstraints()
{
    UWorld* World = GetWorld();
    if (!World) return;

    const FTransform& Transform = GetComponentTransform();

    // Stretch Constraints
    for (int32 i = 0; i < SimCtx.StretchConstraintBuffer.NumBytes / sizeof(FIntPoint); ++i)
    {
        FIntPoint Constraint;
        FMemory::Memcpy(&Constraint, SimCtx.StretchConstraintBuffer.GetData() + i * sizeof(FIntPoint), sizeof(FIntPoint));

        FVector A = Transform.TransformPosition((FVector)SimCtx.Particles[Constraint.X].Position);
        FVector B = Transform.TransformPosition((FVector)SimCtx.Particles[Constraint.Y].Position);

        float Dist = FVector::Distance(A, B);
        float RestLength = 10.0f;
        float Error = FMath::Abs(Dist - RestLength);
        float T = FMath::Clamp(Error / RestLength, 0.0f, 1.0f);
        FColor Color = FColor::MakeRedToGreenColorFromScalar(1.0f - T);

        DrawDebugLine(World, A, B, Color, false, 0.1f, 0, 2.0f);
    }
}

void USailClothComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    FSailClothSimShaders::Release(SimCtx);
    Super::OnComponentDestroyed(bDestroyingHierarchy);
}
