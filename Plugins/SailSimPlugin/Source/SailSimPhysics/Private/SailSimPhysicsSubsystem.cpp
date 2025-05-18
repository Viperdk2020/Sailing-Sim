
#include "SailSimPhysicsSubsystem.h"
#include "SailSimPhysicsManager.h"
#include "RenderGraphBuilder.h"
#include "RHICommandList.h"
//#include "Engine/Engine.h"
#include "SailSimCore/Private/SailClothComponent.h"


void USailSimPhysicsSubsystem::Initialize(FSubsystemCollectionBase&)
{
    // Nothing heavy yet; we allocate on first cloth registration
}

void USailSimPhysicsSubsystem::Deinitialize()
{
}

void USailSimPhysicsSubsystem::RegisterCloth(USailClothComponent* Comp)
{
    if (!Comp) return;

    NumVerts = Comp->GetVertexCount();   // ← your component helper
    CreateBuffers(NumVerts);

    bEnabled = true;                     // begin ticking
}
void USailSimPhysicsSubsystem::SwapBuffers()
{
    ReadIdx ^= 1;
    WriteIdx ^= 1;
}

void USailSimPhysicsSubsystem::KickSim(FRDGBuilder& GraphBuilder, float Dt)
{
    FSailSimPhysicsManager& PM = FSailSimPhysicsManager::Get();

    PM.SimulateFrame(Dt);
}

void USailSimPhysicsSubsystem::Tick(float DeltaTime)
{
   /* if (NumVerts == 0) return;

    FRHICommandListImmediate& RHICmd = GRHICommandList.GetImmediateCommandList();
    FRDGBuilder GraphBuilder(RHICmd);

    // Build physics simulation graph on async‑compute queue
  //  GraphBuilder.SetExecutionFlags(ERDGPassFlags::AsyncCompute);

    FSailSimPhysicsManager& PM = FSailSimPhysicsManager::Get();
    PM.SimulateFrame(
        GraphBuilder,
        Buffers[WriteIdx],
         nullptr, 0, //Stretch
       nullptr, 0,  //Bend
        NumVerts,
        DeltaTime);
    
    // Create a GPU fence so graphics can wait next frame
    if (!SimulationFence.IsValid())
     //   SimulationFence = RHICmd.CreateGPUFence(TEXT("SailSimPhysicsFence"));
   // GraphBuilder.AddExternalAccessFence(SimulationFence);
   // GraphBuilder.Execute();

    // Graphics thread will read Buffers[ReadIdx] this frame
    SwapBuffers();
    */




      if (!bEnabled || !NumVerts) return;

        FRHICommandListImmediate& RHICmd = GRHICommandList.GetImmediateCommandList();
        FRDGBuilder GraphBuilder(RHICmd, RDG_EVENT_NAME("SailSimPhysics"));

        // Ensure previous frame’s async work is done before we overwrite WriteIdx
      //  if (Fence.IsValid())
            RHICmdList.BlockUntilGPUIdle();

        // Kick the simulation on async queue
        KickSim(GraphBuilder, DeltaSeconds);

        // Fence so graphics can safely read Buffers[WriteIdx] next frame
        if (!Fence.IsValid())
            Fence = RHICmd.CreateGPUFence(TEXT("SailSimPhysicsFence"));
        GraphBuilder.AddExternalAccessFence(Fence);

        GraphBuilder.Execute();

        // Swap for next frame (graphics reads new ReadIdx)
        ReadIdx ^= 1;  WriteIdx ^= 1;
    




    
}

TStatId USailSimPhysicsSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(USailSimPhysicsSubsystem, STATGROUP_Tickables);
}
