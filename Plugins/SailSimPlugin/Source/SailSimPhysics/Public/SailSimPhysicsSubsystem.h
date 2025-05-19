// SailSimPhysicsSubsystem.h
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "SailSimPhysicsManager.h"    // your manager’s interface
#include "SailSimPhysicsSubsystem.generated.h"

UCLASS()
class USailSimPhysicsSubsystem : public UEngineSubsystem
{
    GENERATED_BODY()

public:
    /** Called when the engine starts up this subsystem */
    virtual void Initialize(FSubsystemCollectionBase& Collection) override
    {
        Super::Initialize(Collection);

        // Create and initialize your async manager here
       // PhysicsManager = MakeUnique<FSailSimPhysicsManager>();
      //  PhysicsManager->Initialize();   // or whatever your init API is
    }

    /** Called when the engine is shutting down */
    virtual void Deinitialize() override
    {
        if (PhysicsManager)
        {
         //   PhysicsManager->Shutdown(); // clean up threads/queues
          //  PhysicsManager.Reset();
        }
        Super::Deinitialize();
    }

    /** Expose manager if you need to call into it elsewhere */
    FSailSimPhysicsManager* GetPhysicsManager() const
    {
        return PhysicsManager.Get();
    }

private:
    /** Owning pointer to your async manager */
    TUniquePtr<FSailSimPhysicsManager> PhysicsManager;
};



//TStatId USailSimPhysicsSubsystem::GetStatId() const
//{
//    RETURN_QUICK_DECLARE_CYCLE_STAT(USailSimPhysicsSubsystem, STATGROUP_Tickables);
//}
