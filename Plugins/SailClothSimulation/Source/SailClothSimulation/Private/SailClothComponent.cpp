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

    // Allocate CPU-side particle buffer
    ParticleData.SetNum(SimCtx.NumParticles);
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

    // Enqueue readback for constraints
    const uint32 ConstraintSize = SimCtx.NumStretchConstraints * sizeof(FIntPoint);
    if (ConstraintSize > 0) // Only if there are constraints
    {
        if (!ConstraintReadback.IsReady())
        {
            ENQUEUE_RENDER_COMMAND(ReadbackConstraints)(
                [UAV = SimCtx.StretchConstraintBuffer, ReadbackPtr = &ConstraintReadback, ConstraintSize](FRHICommandListImmediate& RHICmdList)
                {
                    ReadbackPtr->EnqueueCopy(RHICmdList, UAV.Buffer, ConstraintSize);
                }
            );
        }
        else
        {
            void* ConstraintData = ConstraintReadback.Lock(ConstraintSize);
            if (ConstraintData)
            {
                StretchConstraints.SetNum(SimCtx.NumStretchConstraints);
                FMemory::Memcpy(StretchConstraints.GetData(), ConstraintData, ConstraintSize);
            }
            ConstraintReadback.Unlock();

            ENQUEUE_RENDER_COMMAND(ReadbackConstraints)(
                [UAV = SimCtx.StretchConstraintBuffer, ReadbackPtr = &ConstraintReadback, ConstraintSize](FRHICommandListImmediate& RHICmdList)
                {
                    ReadbackPtr->EnqueueCopy(RHICmdList, UAV.Buffer, ConstraintSize);
                }
            );
        }
    }

    // Readback and Update Mesh
    ReadbackAndUpdateMesh();
}

void USailClothComponent::ReadbackAndUpdateMesh()
{
    const uint32 NumBytes = SimCtx.NumParticles * sizeof(FParticleGPU);

    // If the GPU has finished writing to the readback buffer, copy the data
    if (ParticleReadback.IsReady())
    {
        void* DataPtr = ParticleReadback.Lock(NumBytes);
        if (DataPtr)
        {
            if (ParticleData.Num() != SimCtx.NumParticles)
            {
                ParticleData.SetNum(SimCtx.NumParticles);
            }

            FMemory::Memcpy(ParticleData.GetData(), DataPtr, NumBytes);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to lock ParticleReadback buffer"));
        }
        ParticleReadback.Unlock();

        // Update the mesh asynchronously to avoid blocking the game thread
        AsyncTask(ENamedThreads::GameThread, [this]()
            {
                if (!ProcMesh) return;

                TArray<FVector> UpdatedVertices;
                UpdatedVertices.SetNum(ParticleData.Num());

                for (int32 i = 0; i < ParticleData.Num(); ++i)
                {
                    UpdatedVertices[i] = FVector(ParticleData[i].Position.X, ParticleData[i].Position.Y, ParticleData[i].Position.Z);
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

    // Enqueue a copy of the latest GPU particle buffer for the next frame
    ENQUEUE_RENDER_COMMAND(ReadbackParticles)(
        [UAV = SimCtx.ParticleBuffer, ReadbackPtr = &ParticleReadback, NumBytes](FRHICommandListImmediate& RHICmdList)
        {
            ReadbackPtr->EnqueueCopy(RHICmdList, UAV.Buffer, NumBytes);
        }
    );
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

    const FTransform& Transform = GetOwner()->GetRootComponent()->GetComponentTransform();

    int32 NumConstraints = StretchConstraints.Num();
    if (NumConstraints == 0) return;

    for (int32 i = 0; i < NumConstraints; ++i)
    {
        const FIntPoint& Constraint = StretchConstraints[i];

        if (!ParticleData.IsValidIndex(Constraint.X) || !ParticleData.IsValidIndex(Constraint.Y))
            continue;

        FVector A = Transform.TransformPosition(FVector(
            ParticleData[Constraint.X].Position.X,
            ParticleData[Constraint.X].Position.Y,
            ParticleData[Constraint.X].Position.Z));
        FVector B = Transform.TransformPosition(FVector(
            ParticleData[Constraint.Y].Position.X,
            ParticleData[Constraint.Y].Position.Y,
            ParticleData[Constraint.Y].Position.Z));

        float Dist = FVector::Distance(A, B);
        float RestLength = 10.0f;
        float Error = FMath::Abs(Dist - RestLength);
        float T = FMath::Clamp(Error / RestLength, 0.0f, 1.0f);
        FColor Color = FColor::MakeRedToGreenColorFromScalar(1.0f - T);

        DrawDebugLine(World, A, B, Color, false, 0.1f, 0, 2.0f);
    }
}

void USailClothComponent::RebuildStripsFromSimData(const FSailClothSimContext* SimCtx, int32 GridWidth, int32 GridHeight)
{
    Strips.Empty();

    if (!SimCtx || ParticleData.Num() == 0)
    {
        return;
    }

    // For each strip (column), compute aerodynamic properties
    for (int32 x = 0; x < GridWidth; ++x)
    {
        FSailStrip Strip;
        FVector3f AccumPos = FVector3f(0, 0, 0);
        FVector3f AccumNormal = FVector3f(0, 0, 0);
        float AccumChord = 0.0f;
        float AccumGamma = 0.0f;
        float AccumCl = 0.0f;
        float AccumCd = 0.0f;
        float AccumTwist = 0.0f;
        float AccumTrim = 0.0f;
        int32 Count = 0;

        for (int32 y = 0; y < GridHeight; ++y)
        {
            int32 Index = y * GridWidth + x;
            if (ParticleData.IsValidIndex(Index))
            {
                const FParticleGPU& Particle = ParticleData[Index];
                AccumPos += Particle.Position;
                AccumNormal += Particle.Normal;
                // If you have per-particle chord/gamma/Cl/Cd/Twist/Trim, accumulate here
                ++Count;
            }
        }

        if (Count > 0)
        {
            Strip.Position = AccumPos / static_cast<float>(Count);
            Strip.Normal = AccumNormal.GetSafeNormal();
            Strip.Chord = AccumChord / FMath::Max(1, Count);
            Strip.Gamma = AccumGamma / FMath::Max(1, Count);
            Strip.Cl = AccumCl / FMath::Max(1, Count);
            Strip.Cd = AccumCd / FMath::Max(1, Count);
            Strip.TwistAngleDeg = AccumTwist / FMath::Max(1, Count);
            Strip.SailTrimAngleDeg = AccumTrim / FMath::Max(1, Count);
            Strips.Add(Strip);
        }
    }
}

void USailClothComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    FSailClothSimShaders::Release(SimCtx);
    Super::OnComponentDestroyed(bDestroyingHierarchy);
}
