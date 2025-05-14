#include "Components/SailClothComponent.h"
USailClothComponent::USailClothComponent() {
    PrimaryComponentTick.bCanEverTick = true;
}
void USailClothComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}