#pragma once

#include <vector>
#include "worldobject.h"
#include "world/world.h"
#include "world/god.h"
#include "property/propertymanager.h"
#include "property/property.h"

class World;
class God;
class Hardpoint;
class Engine;

class Ship : public WorldObject {
public:
    Ship();
    virtual void update(float deltasec);

    virtual void addHardpointVoxel(HardpointVoxel* voxel);
    void removeHardpoint(Hardpoint* hardpoint);
    virtual void addEngineVoxel(EngineVoxel* voxel);
    void removeEngine(Engine* engine);

    void setTargetObject(WorldObject* target);
    WorldObject* targetObject();
    void fireAtPoint(glm::vec3 target);
    void fireAtObject();
    float minAimDistance();

    virtual void accelerate(const glm::vec3& direction) override;
    virtual void accelerateAngular(const glm::vec3& axis) override;

protected:

    Property<float> prop_maxSpeed;
    Property<float> prop_maxRotSpeed;
    
	std::vector<Hardpoint*> m_hardpoints;
    std::vector<Engine*> m_engines;
    WorldObject* m_targetObject;
};
