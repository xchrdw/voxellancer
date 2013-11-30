#pragma once

#include <set>
#include <list>

#include "impact.h"


class WorldObject;

class Damager
{
public:
    void applyDamages(std::list<Impact> &impacts);

    std::list<Impact> &dampedDeadlyImpacts();
    std::list<Impact> &deadlyImpacts();
    std::set<WorldObject*> &modifiedWorldObjects();


protected:
    std::list<Impact> m_dampedDeadlyImpacts;
    std::list<Impact> m_deadlyImpacts;
    std::set<WorldObject*> m_modifiedVoxelClusters;

    float damageOfImpact(const Impact &impact) const;
    Impact dampImpact(Impact &undamped, float factor);
};
