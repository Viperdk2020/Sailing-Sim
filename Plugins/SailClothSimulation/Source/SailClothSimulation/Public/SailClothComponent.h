#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RHIResources.h"
#include "SailClothSimShaders.h"
#include "ProceduralMeshComponent.h"
#include "SailClothComponent.generated.h"

/**
 * Sail Cloth Simulation Component
 * Handles GPU-based cloth simulation and aerodynamic processing for sails.
 */
UCLASS(ClassGroup = Physics, meta = (BlueprintSpawnableComponent, DisplayName = "Sail Cloth Simulation"))
class USailClothComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USailClothComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    /**
     * Rebuild strips from simulation data for aerodynamic calculations.
     */
    void RebuildStripsFromSimData(const FSailClothSimContext* SimCtx, int32 GridWidth, int32 GridHeight);

    /**
     * Get the current aerodynamic strips for debug or analysis.
     */
//    UFUNCTION(BlueprintCallable, Category = "Sail Cloth")
    const TArray<FSailStrip>& GetSailStrips() const { return Strips; }

protected:
    void CreateInitialMesh(int32 GridWidth, int32 GridHeight);
    void ReadbackAndUpdateMesh();
    void VisualizeConstraints();

private:
    FSailClothSimContext SimCtx;

    /** Parent component */
    USceneComponent* ParentComp = nullptr;

    /** Procedural mesh component */
    UPROPERTY()
    UProceduralMeshComponent* ProcMesh;

    /** GPU readback buffer for particle data */
    FRHIGPUBufferReadback ParticleReadback{ TEXT("SailClothParticleReadback") };
    // Add this line to define ConstraintReadback as an instance of FRHIGPUBufferReadback
    FRHIGPUBufferReadback ConstraintReadback{ TEXT("SailClothConstraintReadback")};

    /** Cached particle data (CPU side) */
    TArray<FParticleGPU> ParticleData;
    TArray<float> GammaData;

    /** Constraint data */
    TArray<FIntPoint> StretchConstraints;
    TArray<float> StretchRestLengths;
    TArray<FIntPoint> BendConstraints;
    TArray<float> BendRestAngles;

    /** Aerodynamic strip data */
    TArray<FSailStrip> Strips;
};

/**
 * Aerodynamic strip data structure for VLM and debugging.
 */
USTRUCT(BlueprintType)
struct SAILCLOTHSIMULATION_API FSailStrip
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Sail Strip")
    FVector3f Position;

    UPROPERTY(BlueprintReadOnly, Category = "Sail Strip")
    FVector3f Normal;

    UPROPERTY(BlueprintReadOnly, Category = "Sail Strip")
    float Chord = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Sail Strip")
    float Gamma = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Sail Strip")
    float Cl = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Sail Strip")
    float Cd = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Sail Strip")
    float TwistAngleDeg = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Sail Strip")
    float SailTrimAngleDeg = 0.0f;
};
