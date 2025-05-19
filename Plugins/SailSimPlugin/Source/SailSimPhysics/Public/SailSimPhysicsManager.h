
#pragma once
#include "CoreMinimal.h"
#include "RenderGraphResources.h"
#include <vector>

class FSailSimSailPhysicsManager;

/** Boat‑level physics orchestrator (ticks all sail runners & future rope/hull) */
class SAILSIMPHYSICS_API FSailSimPhysicsManager
{
public:
    static FSailSimPhysicsManager& Get();

    void AddSail(FSailSimSailPhysicsManager* Sail);
    bool HasSails() const { return !Sails.empty(); }

    /** build simulation for all sails */
    void SimulateFrame(FRDGBuilder& GraphBuilder, float DeltaTime);

private:
    std::vector<FSailSimSailPhysicsManager*> Sails;
};
