#include "engineslot.h"

#include <cassert>

#include "voxel/specialvoxels/engineslotvoxel.h"

#include "equipment/engine.h"
#include "worldobject/worldobjectcomponents.h"


EngineSlot::EngineSlot(WorldObjectComponents* components, EngineSlotVoxel* voxel):
    WorldObjectSlot(components, voxel->index()),
    m_voxel(voxel),
    m_engine(nullptr)
{
}

const EngineSlotVoxel* EngineSlot::voxel() const{
    return m_voxel;
}

const glm::vec3& EngineSlot::direction() {
    return m_direction;
}

void EngineSlot::setDirection(const glm::vec3& direction) {
    m_direction = direction;
}

const std::shared_ptr<Engine>& EngineSlot::engine() {
    return m_engine;
}

void EngineSlot::setEngine(const std::shared_ptr<Engine>& engine) {
    assert(mountable(engine->equipmentKey()));

    bool changed = m_engine != engine;

    if (changed && m_engine) {
        m_engine->setEngineSlot(nullptr);
    }

    m_engine = engine;

    if (m_engine) {
        m_engine->setEngineSlot(this);
    }

    if (changed) {
        notifyObservers();
    }
}

void EngineSlot::update(float deltaSec) {
    if(m_engine) {
        m_engine->update(deltaSec);
    }
}

void EngineSlot::onVoxelRemoval() {
    m_components->removeEngineSlot(this);
}

