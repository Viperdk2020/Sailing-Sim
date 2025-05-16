
#include "SailSimPhysicsSubsystem.h"
#include "SailSimPhysicsManager.h"
#include "RenderGraphBuilder.h"
#include "RHICommandList.h"
#include "Engine/Engine.h"

void USailSimPhysicsSubsystem::Initialize(FSubsystemCollectionBase&){}

void USailSimPhysicsSubsystem::Deinitialize(){}

void USailSimPhysicsSubsystem::SwapBuffers()
{
    ReadIdx ^= 1;
    WriteIdx ^= 1;
}

void USailSimPhysicsSubsystem::Tick(float DeltaTime)
{
    if (NumVerts == 0) return;

    FRHICommandListImmediate& RHICmd = GRHICommandList.GetImmediateCommandList();
    FRDGBuilder GraphBuilder(RHICmd);

    // Build physics simulation graph on async‑compute queue
    GraphBuilder.SetExecutionFlags(ERDGPassFlags::AsyncCompute);

    FSailSimPhysicsManager& PM = FSailSimPhysicsManager::Get();
    PM.SimulateFrame(
        GraphBuilder,
        Buffers[WriteIdx],
        /*Stretch*/ nullptr, 0,
        /*Bend*/ nullptr, 0,
        NumVerts,
        DeltaTime);

    // Create a GPU fence so graphics can wait next frame
    if (!SimulationFence.IsValid())
        SimulationFence = RHICmd.CreateGPUFence(TEXT("SailSimPhysicsFence"));
    GraphBuilder.AddExternalAccessFence(SimulationFence);
    GraphBuilder.Execute();

    // Graphics thread will read Buffers[ReadIdx] this frame
    SwapBuffers();
}

TStatId USailSimPhysicsSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(USailSimPhysicsSubsystem, STATGROUP_Tickables);
}
