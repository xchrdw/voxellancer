#pragma once

#include <list>

#include "collision/worldobjectcollision.h"

#include "property/property.h"

#include "world/helper/damageimpact.h"
#include "world/helper/voxelaccumulator.h"


class DamageImpactGenerator {
public:
    DamageImpactGenerator();

    void parse(std::list<WorldObjectCollision>& worldObjectCollisions);
    void parse(std::list<DamageImpact>& damageImpact);

    std::list<DamageImpact>& damageImpacts();


protected:
    VoxelAccumulator<DamageImpact> m_damageImpactAccumulator;
    Property<float> m_elasticity;
};

