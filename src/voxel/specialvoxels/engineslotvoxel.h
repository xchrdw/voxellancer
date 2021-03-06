#pragma once

#include <memory>

#include "voxel/specialvoxel.h"


class EngineSlot;

class EngineSlotVoxel: public SpecialVoxel {
public:
    EngineSlotVoxel(const glm::ivec3& cell, int index);

    virtual Visuals visuals() const override;

    virtual void addToObject(WorldObject* worldObject) override;

    virtual void onRemoval() override;
    virtual void onDestruction() override;


protected:
    std::shared_ptr<EngineSlot> m_engineSlot;
};

