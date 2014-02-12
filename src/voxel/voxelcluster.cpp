#include "voxelcluster.h"

#include <iostream>
#include <list>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <glow/ChangeListener.h>
#include <glow/logging.h>

#include "utils/tostring.h"
#include "voxelrenderdata.h"
#include "voxel.h"


VoxelCluster::VoxelCluster(float scale):
    m_voxels(),
    m_bounds(this),
    m_voxelRenderData(new VoxelRenderData(m_voxels)),
    m_transform(glm::vec3(0), scale)
{
}

VoxelCluster::~VoxelCluster() {
    for (auto& element : m_voxels) {
        delete element.second;
    }
}

VoxelClusterBounds& VoxelCluster::bounds() {
    return m_bounds;
}

Transform& VoxelCluster::transform() {
    return m_transform;
}

const Transform& VoxelCluster::transform() const {
    return m_transform;
}

void VoxelCluster::setTransform(const Transform& transform) {
    m_transform = transform;
}

Voxel* VoxelCluster::voxel(const glm::ivec3& position) {
    std::unordered_map<glm::ivec3, Voxel*>::iterator i = m_voxels.find(position);
    return i == m_voxels.end() ? nullptr : i->second;
}

void VoxelCluster::addVoxel(Voxel* voxel) {
    assert(m_voxels[voxel->gridCell()] == nullptr);

    m_voxels[voxel->gridCell()] = voxel;
    m_bounds.addVoxel(voxel);
    m_voxelRenderData->invalidate();
}

void VoxelCluster::removeVoxel(Voxel* voxel) {
    assert(voxel != nullptr);

    m_bounds.removeVoxel(voxel); // Needs to be done before removal from m_voxels
    m_voxels.erase(voxel->gridCell());
    m_voxelRenderData->invalidate();

    delete voxel;
}

VoxelRenderData* VoxelCluster::voxelRenderData() {
    return m_voxelRenderData.get();
}

const std::unordered_map<glm::ivec3, Voxel*>& VoxelCluster::voxelMap() const {
    return m_voxels;
}

int VoxelCluster::voxelCount() const {
    return m_voxels.size();
}

void VoxelCluster::rotate(const glm::quat& rotation) {
    m_transform.rotate(rotation);
}

void VoxelCluster::move(const glm::vec3& vec3) {
    m_transform.move(vec3);
}

const glm::vec3& VoxelCluster::position() {
    return m_transform.position();
}

const glm::quat& VoxelCluster::orientation() {
    return m_transform.orientation();
}

void VoxelCluster::setOrientation(const glm::quat& orientation) {
    m_transform.setOrientation(orientation);
}

void VoxelCluster::setPosition(const glm::vec3& pos) {
    m_transform.setPosition(pos);
}

float VoxelCluster::emissiveness() {
    return 0.0f;
}

