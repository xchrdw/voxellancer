#pragma once

#include <unordered_map>

#include <GL/glew.h>

#include <glow/ref_ptr.h>

#include "utils/vec3hash.h"


namespace glow {
    class Program;
    class VertexArrayObject;
    class Buffer;
    class Texture;
};
class Voxel;

class VoxelRenderData
{
public:
    VoxelRenderData(std::unordered_map<glm::ivec3, Voxel*> &voxel);
    ~VoxelRenderData();

    void invalidate();
    int voxelCount();

    glow::VertexArrayObject* vertexArrayObject();

private:
    std::unordered_map<glm::ivec3, Voxel*> &m_voxel;
    bool m_isDirty;
    int m_bufferSize;

    glow::ref_ptr<glow::Buffer> m_voxelDataBuffer;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;

    void updateBuffer();
    void setupVertexAttributes();
    void setupVertexAttribute(GLint offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum);

};

