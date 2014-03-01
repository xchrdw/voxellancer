#pragma once

#include <memory>

class Voxel;
class WorldObject;
class VoxelTreeNode;

class IVoxelTree {
public:

    virtual void insert(Voxel* voxel) = 0;
    virtual void remove(Voxel* voxel) = 0;

    virtual bool isInstanced() = 0;

    virtual VoxelTreeNode* root() = 0;
};

class InstancedVoxelTree : public IVoxelTree {
public:
    InstancedVoxelTree(IVoxelTree& prototype);

    virtual void insert(Voxel* voxel) override; // ignore
    virtual void remove(Voxel* voxel) override; // ignore

    virtual bool isInstanced() override;

    virtual VoxelTreeNode* root() override;

protected:
    IVoxelTree& m_prototype;
};

class VoxelTree : public IVoxelTree {
public:
    VoxelTree(WorldObject* worldObject);
    virtual ~VoxelTree();

    virtual void insert(Voxel* voxel) override;
    virtual void remove(Voxel* voxel) override;

    virtual bool isInstanced();
    
    virtual VoxelTreeNode* root() override;
    WorldObject* worldObject();

protected:
    VoxelTreeNode* m_shadowRoot;
    VoxelTreeNode* m_currentRoot;
    WorldObject* m_worldObject;
};
