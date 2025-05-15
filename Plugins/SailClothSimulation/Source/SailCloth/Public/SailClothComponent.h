#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SailClothComponent.generated.h"

class FSailPhysicsManager;
class FSailRenderManager;

USTRUCT(BlueprintType)
struct FSailSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sail")
    int32 NumVertices = 1024;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sail")
    float WindStrength = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sail")
    FVector WindDirection = FVector(1.0f, 0.0f, 0.0f);
};

UCLASS(ClassGroup=(Sail), meta=(BlueprintSpawnableComponent))
class SAILCLOTH_API USailClothComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USailClothComponent();

    virtual void InitializeComponent() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    TSharedPtr<FSailPhysicsManager> PhysicsManager;
    TUniquePtr<FSailRenderManager> RenderManager;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sail Settings", meta=(AllowPrivateAccess="true"))
    FSailSettings SailSettings;
};