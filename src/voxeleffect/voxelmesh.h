#pragma once

#include <string>

#include <glow/ref_ptr.h>
#include <glow/Array.h>

#include <glm/glm.hpp>


namespace glow {
    class Program;
    class VertexArrayObject;
    class Buffer;
};


class VoxelMesh {
public:
    static void bindTo(glow::Program* program,
                       glow::VertexArrayObject* vao,
                       int bindingIndex);
    static void tearDown();


protected:
    static glow::ref_ptr<glow::Buffer> s_vertexBuffer;


    static void setupVertexAttribute(glow::Program* program, glow::VertexArrayObject* vao, const std::string& name, GLboolean normalised, int bindingNum, GLint offset);
    static glow::Buffer* vertexBuffer();
    static void initBuffer();
};
