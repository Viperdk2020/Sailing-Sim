
#include "SailSimPhysicsSubsystem.h"
#include "SailSimPhysicsManager.h"
#include "RenderGraphBuilder.h"
#include "RHICommandList.h"

void USailSimPhysicsSubsystem::Initialize(FSubsystemCollectionBase&)
{
    Manager = &FSailSimPhysicsManager::Get();
}

void USailSimPhysicsSubsystem::Deinitialize()
{
    Manager = nullptr;
}

void USailSimPhysicsSubsystem::Tick(float Dt)
{
    if(!Manager || !Manager->HasSails()) return;

    FRHICommandListImmediate& RHICmd = GRHICommandList.GetImmediateCommandList();
    FRDGBuilder Graph(RHICmd, RDG_EVENT_NAME("SailSimBoat"));

    if(Fence.IsValid())
        RHICmd.WaitForFence(Fence);

    Manager->SimulateFrame(Graph, Dt);

    if(!Fence.IsValid())
        Fence = RHICmd.CreateGPUFence(TEXT("SailSimBoatFence"));
    Graph.AddExternalAccessFence(Fence);

    Graph.Execute();
}

TStatId USailSimPhysicsSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(USailSimPhysicsSubsystem, STATGROUP_Tickables);
}
