#include "Components/SailClothComponent.h"


void USailClothComponent::InitializeComponent()
{
    Super::InitializeComponent();
    PhysicsManager = MakeShared<FSailPhysicsManager>();
    PhysicsManager->Initialize(SailSettings.NumVertices);

   // RenderManager = MakeUnique<FSailRenderManager>();
   // RenderManager->Initialize(PhysicsManager.Get(), this);
}

void USailClothComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PhysicsManager.IsValid())
    {
     //   PhysicsManager->Tick(DeltaTime);
    }

    if (RenderManager.IsValid())
    {
       // RenderManager->Tick();
    }
}

