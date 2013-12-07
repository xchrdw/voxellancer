#include "splitdetector.h"

#include <unordered_set>

#include "world/helper/worldobjectsplit.h"

#include "voxel/voxel.h"
#include "voxel/voxelneighbourhelper.h"

#include "worldobject/worldobject.h"
#include <queue>


void SplitDetector::searchSplitOffs(std::list<WorldObjectModification> worldObjectModifications) {
    clear();

    for(WorldObjectModification& worldObjectModification : worldObjectModifications) {
        WorldObject* currentWorldObject = worldObjectModification.worldObject();
        VoxelNeighbourHelper nHelper(currentWorldObject);
        std::unordered_set<Voxel*> borderVoxels;
        for (glm::ivec3 removedPos : worldObjectModification.removedVoxels())
        {
            for (Voxel * voxel : nHelper.neighbours(removedPos)) {
                borderVoxels.insert(voxel);
            }
        }
        findSplits(currentWorldObject, borderVoxels);
    }
}


std::list<WorldObjectSplit*> &SplitDetector::worldObjectSplits() {
    return m_worldObjectSplits;
}

void SplitDetector::clear() {
    for(WorldObjectSplit *split : m_worldObjectSplits) {
        delete split;
    }

    m_worldObjectSplits.clear();
}

void SplitDetector::findSplits(WorldObject* currentWorldObject, std::unordered_set<Voxel*>& borderVoxel, bool addLastSplit) {
    assert(borderVoxel.size() > 0);
    VoxelNeighbourHelper nHelper(currentWorldObject);
    std::unordered_set<Voxel *> seen;
    std::queue<Voxel *> toVisit;

    // add one voxel from the border
    Voxel* start = *borderVoxel.begin();
    borderVoxel.erase(start);
    seen.insert(start);
    toVisit.push(start);
    
    // breadth first search for other border voxels
    while ((borderVoxel.size() > 0 || addLastSplit) && toVisit.size() > 0) {
        Voxel * current = toVisit.front();
        toVisit.pop();

        for (Voxel * voxel : nHelper.neighbours(current)) {
            if (!seen.count(voxel)) {
                borderVoxel.erase(voxel);
                seen.insert(voxel);
                toVisit.push(voxel);
            }
        }
    }
    
    if (borderVoxel.size() > 0 || addLastSplit) {
        if (currentWorldObject->crucialVoxel() == nullptr || seen.count(currentWorldObject->crucialVoxel()) == 0) {
            createSplit(currentWorldObject, seen);
        }
    }
    if (borderVoxel.size() > 1 || currentWorldObject->crucialVoxel() != nullptr && borderVoxel.size() > 0) {
        findSplits(currentWorldObject, borderVoxel, currentWorldObject->crucialVoxel() != nullptr);
    }
}

void SplitDetector::createSplit(WorldObject* currentWorldObject, std::unordered_set<Voxel *>& splitVoxels) {
    WorldObjectSplit * split = new WorldObjectSplit();
    split->setExWorldObject(currentWorldObject);
    for (Voxel * voxel : splitVoxels) {
        split->addVoxel(voxel);
    }
    m_worldObjectSplits.push_back(split);
}



