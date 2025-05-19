
#include "SailSimPhysicsManager.h"
#include "SailSimSailPhysicsManager.h"

FSailSimPhysicsManager& FSailSimPhysicsManager::Get()
{
    static FSailSimPhysicsManager GInstance;
    return GInstance;
}

void FSailSimPhysicsManager::AddSail(FSailSimSailPhysicsManager* Sail)
{
    if (!Sail) return;
    Sails.push_back(Sail);
}

void FSailSimPhysicsManager::SimulateFrame(FRDGBuilder& Graph, float Dt)
{
    for (FSailSimSailPhysicsManager* Sail : Sails)
    {
        Sail->Simulate(Graph, Dt);
    }
}
