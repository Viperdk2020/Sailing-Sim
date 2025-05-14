#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SailClothComponent.generated.h"
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SAILCLOTHSIMULATION_API USailClothComponent : public UActorComponent {
    GENERATED_BODY()
public:
    USailClothComponent();
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};