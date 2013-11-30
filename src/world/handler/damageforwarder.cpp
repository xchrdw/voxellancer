#include "damageforwarder.h"

#include <algorithm>
#include <glm/glm.hpp>

#include "voxel/voxelcluster.h"
#include "voxel/voxeltreenode.h"


void DamageForwarder::forwardDamage(std::list<Impact> &dampedDeadlyImpacts) {
    m_forwardedDamageImpacts.clear();

    for(Impact &dampedDeadlyImpact : dampedDeadlyImpacts) {
        Voxel *deadVoxel = dampedDeadlyImpact.voxel();

        m_currentWorldObject = dampedDeadlyImpact.worldObject();
        std::list<Voxel*> neighbours = getNeighbours(deadVoxel);

        glm::vec3 impactVec = glm::normalize(dampedDeadlyImpact.vec());

        for(Voxel *neighbour : neighbours) {
            glm::vec3 voxelVec = glm::normalize(neighbour->position() - deadVoxel->position());
            float dotProduct = glm::dot(impactVec, voxelVec);

            if(dotProduct >= 0.0f) {
                Impact forwarded(m_currentWorldObject, neighbour, impactVec * dotProduct);
                m_forwardedDamageImpacts.push_back(forwarded);
            }
        }
    }
}

std::list<Impact> &DamageForwarder::forwardedDamageImpacts() {
    return m_forwardedDamageImpacts;
}

std::list<Voxel*> DamageForwarder::getNeighbours(Voxel *voxel) {
    std::list<Voxel*> neighbours;

    m_currentNeighbours = &neighbours;
    m_currentGridCell = voxel->gridCell();

    considerNeighbour(glm::ivec3(-1, 0, 0));
    considerNeighbour(glm::ivec3(+1, 0, 0));
    considerNeighbour(glm::ivec3(0, -1, 0));
    considerNeighbour(glm::ivec3(0, +1, 0));
    considerNeighbour(glm::ivec3(0, 0, -1));
    considerNeighbour(glm::ivec3(0, 0, +1));

    return neighbours;
}

void DamageForwarder::considerNeighbour(const glm::ivec3 &cellDelta) {
    VoxeltreeNode &voxeltree = m_currentVoxelCluster->voxeltree();
    const Grid3dAABB &grid = voxeltree.gridAABB();

    Voxel *neighbour = m_currentVoxelCluster->voxel(cell);
    if(neighbour == nullptr) {
        return;
    }

    m_currentNeighbours->push_back(neighbour);
}

