#include "worldobject.h"


WorldObject::WorldObject():
    m_transform(),
    m_voxelCluster(),
    m_physics(*this),
    m_collisionDetector(*this)
{

}

CollisionDetector * WorldObject::collisionDetector()
{
    return &m_collisionDetector;
}

AABB WorldObject::aabb() {
    return m_voxelCluster.aabb(m_transform);
}

Sphere WorldObject::sphere() {
    return m_voxelCluster.sphere(m_transform);
}

void WorldObject::update(float delta_sec)
{

}

void WorldObject::move(float delta_sec)
{
    m_physics.move(delta_sec);
}

void WorldObject::addVoxel(Voxel * voxel)
{
    m_voxelCluster.addVoxel(voxel);
    m_physics.addVoxel(voxel);
    m_collisionDetector.addVoxel(voxel);
}

void WorldObject::removeVoxel(const cvec3 & position)
{
    m_voxelCluster.removeVoxel(position);
    m_physics.removeVoxel(position);
    m_collisionDetector.removeVoxel(position);
}

glm::mat4 WorldObject::matrix()
{
    return m_transform.matrix();
}

WorldTransform& WorldObject::transform()
{
    return m_transform;
}
