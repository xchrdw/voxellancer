#include "worldobjectcomponents.h"

#include <algorithm>

#include "worldobject/components/engineslot.h"
#include "worldobject/components/engine.h"
#include "worldobject/components/hardpoint.h"
#include "worldobject/components/weapon.h"
#include "worldobject/components/weapons/gun.h"
#include "worldobject/components/weapons/rocketlauncher.h"


WorldObjectComponents::WorldObjectComponents(WorldObject* worldObject):
    m_worldObject(worldObject)
{
}

WorldObject* WorldObjectComponents::worldObject() {
    return m_worldObject;
}

void WorldObjectComponents::addEngineSlot(std::shared_ptr<EngineSlot> engineSlot) {
    m_engineSlots.push_back(engineSlot);
}

void WorldObjectComponents::removeEngineSlot(std::shared_ptr<EngineSlot> engineSlot) {
    m_engineSlots.remove(engineSlot);
}

std::shared_ptr<EngineSlot> WorldObjectComponents::engineSlot(int index) {
    std::list<std::shared_ptr<EngineSlot>>::iterator i = std::find_if(m_engineSlots.begin(), m_engineSlots.end(), [&](std::shared_ptr<EngineSlot> engineSlot) {
        return engineSlot->index() == index;
    });
    return (i == m_engineSlots.end()) ? nullptr : *i;
}

std::list<std::shared_ptr<EngineSlot>>& WorldObjectComponents::engineSlots() {
    return m_engineSlots;
}

EnginePower WorldObjectComponents::enginePower() const {
    EnginePower accumulated;
    for (std::shared_ptr<EngineSlot> engineSlot : m_engineSlots) {
        if (engineSlot->engine()) {
            accumulated += engineSlot->engine()->power();
        }
    }
    return accumulated;
}

Acceleration WorldObjectComponents::currentAcceleration() const {
    Acceleration accumulated;
    for (std::shared_ptr<EngineSlot> engineSlot : m_engineSlots) {
        if (engineSlot->engine()) {
            accumulated += engineSlot->engine()->currentAcceleration();
        }
    }
    return accumulated;

}

const EngineState& WorldObjectComponents::engineState() const {
    return m_engineState;
}

void WorldObjectComponents::setEngineState(const EngineState& engineState) {
    m_engineState = engineState;

    for (std::shared_ptr<EngineSlot> engineSlot : m_engineSlots) {
        if (engineSlot->engine()) {
            engineSlot->engine()->setState(engineState);
        }
    }
}

void WorldObjectComponents::addHardpoint(std::shared_ptr<Hardpoint> hardpoint) {
    m_hardpoints.push_back(hardpoint);
}

void WorldObjectComponents::removeHardpoint(std::shared_ptr<Hardpoint> hardpoint) {
    m_hardpoints.remove(hardpoint);
}

std::shared_ptr<Hardpoint> WorldObjectComponents::hardpoint(int index) {
    std::list<std::shared_ptr<Hardpoint>>::iterator i = std::find_if(m_hardpoints.begin(), m_hardpoints.end(), [&](std::shared_ptr<Hardpoint> hardpoint) {
        return hardpoint->index() == index;
    });
    return i == m_hardpoints.end() ? nullptr : *i;
}

std::list<std::shared_ptr<Hardpoint>>& WorldObjectComponents::hardpoints() {
    return m_hardpoints;
}

void WorldObjectComponents::fireAtPoint(const glm::vec3& point) {
    for (std::shared_ptr<Hardpoint> hardpoint : m_hardpoints) {
        if (hardpoint->weapon() && hardpoint->weapon()->type() == WeaponType::Gun) {
            Gun& gun = dynamic_cast<Gun&>(*hardpoint->weapon().get());
            gun.fireAtPoint(point);
        }
    }
}

void WorldObjectComponents::fireAtObject(WorldObject* worldObject) {
    assert(worldObject);

    for (std::shared_ptr<Hardpoint> hardpoint : m_hardpoints) {
        if(!hardpoint->weapon()) {
            continue;
        }
        if (hardpoint->weapon()->type() == WeaponType::RocketLauncher) {
            RocketLauncher& rocketLauncher = dynamic_cast<RocketLauncher&>(*hardpoint->weapon());
            rocketLauncher.fireAtObject(worldObject);
        }
    }
}

void WorldObjectComponents::update(float deltaSec) {
    for (std::shared_ptr<Hardpoint> hardpoint : m_hardpoints) {
        hardpoint->update(deltaSec);
    }

    for (std::shared_ptr<EngineSlot> engineSlot : m_engineSlots) {
        engineSlot->update(deltaSec);
    }
}


