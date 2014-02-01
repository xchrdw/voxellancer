#pragma once

#include <glm/glm.hpp>

#include "property/property.h"
#include "voxeleffect/voxelexplosiongenerator.h"


class Engine;
class WorldObject;

class EngineTrailGenerator
{
public:
    EngineTrailGenerator(Engine* engine);
    virtual ~EngineTrailGenerator();

    void setFrequency(float frequency);

    void update(float deltaSec);

protected:
    glm::vec3 calculateSpawnPosition();
    void spawnAt(glm::vec3 position);

    Engine* m_engine;
    WorldObject* m_worldObject;
    VoxelExplosionGenerator m_generator;
    float m_spawnOffset;

    glm::vec3 m_lastPosition;
    bool m_lastValid;
    double m_timeSinceLastSpawn;

    Property<float> prop_lifetime, prop_stepDistance, prop_idleTime;
};

