#pragma once

#include "property/property.h"

#include "voxelparticleremovecheck.h"


class VoxelParticleEngine;
struct VoxelParticleData;


/*
    Regular check that removes particles that intersect with WorldObjects
*/
class VoxelParticleIntersectionCheck: public VoxelParticleRemoveCheck {
public:
    VoxelParticleIntersectionCheck(VoxelParticleEngine* engine);

    virtual void update(float deltaSec) override;


protected:
    Property<float> m_fullDeadCheckInterval;

    virtual bool check(VoxelParticleData* particleData) override;
    virtual bool isParallel(int checkCount) override;
};
