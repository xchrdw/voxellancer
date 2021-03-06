#include "crucialvoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"

#include "worldobject/worldobject.h"


CrucialVoxel::CrucialVoxel(const glm::ivec3& cell, int index):
    SpecialVoxel(cell, Property<uint32_t>::get("voxels.crucial.color"), index, Property<float>::get("voxels.crucial.density"), Property<float>::get("voxels.crucial.hp"))
{
}

void CrucialVoxel::addToObject(WorldObject* worldObject){
    assert(worldObject->crucialVoxel() == nullptr);

    Voxel::addToObject(worldObject);
    worldObject->setCrucialVoxel(m_gridCell);
}

void CrucialVoxel::onRemoval(){
    //TODO: Destroy ship / make wreckage?
}

void CrucialVoxel::onDestruction(){
    Voxel::onDestruction();
}

