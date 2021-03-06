#pragma once

#include "voxel/specialvoxel.h"


class CrucialVoxel: public SpecialVoxel {
public:
    CrucialVoxel(const glm::ivec3& cell, int index);

    virtual void addToObject(WorldObject* worldObject) override;

    virtual void onRemoval() override;
    virtual void onDestruction() override;
};
