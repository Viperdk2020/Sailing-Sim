#include "SailClothComponent.h"
#include "SailClothPhysics/Public/SailPhysicsManager.h"
#include "SailClothRendering/Public/SailRenderManager.h"

USailClothComponent::USailClothComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USailClothComponent::InitializeComponent()
{
    Super::InitializeComponent();

    // Initialize physics manager
    PhysicsManager = MakeShared<FSailPhysicsManager>();
    PhysicsManager->Initialize(SailSettings.NumVertices);

    // Initialize render manager
    RenderManager = MakeUnique<FSailRenderManager>();
    RenderManager->Initialize(PhysicsManager.Get(), this);
}

void USailClothComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PhysicsManager.IsValid())
    {
        PhysicsManager->Tick(DeltaTime);
    }

    if (RenderManager.IsValid())
    {
        RenderManager->Tick();
    }
}