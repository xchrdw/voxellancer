#include "voxelmesh.h"
#include <glow/Buffer.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/Program.h>

static const glm::vec3 llf(-.5f, -.5f, -.5f);
static const glm::vec3 llb(-.5f, -.5f, .5f);
static const glm::vec3 luf(-.5f, .5f, -.5f);
static const glm::vec3 lub(-.5f, .5f, .5f);
static const glm::vec3 rlf(.5f, -.5f, -.5f);
static const glm::vec3 rlb(.5f, -.5f, .5f);
static const glm::vec3 ruf(.5f, .5f, -.5f);
static const glm::vec3 rub(.5f, .5f, .5f);

static const glm::vec3 left(-1, 0, 0);
static const glm::vec3 right(1, 0, 0);
static const glm::vec3 bottom(0, -1, 0);
static const glm::vec3 top(0, 1, 0);
static const glm::vec3 front(0, 0, -1);
static const glm::vec3 back(0, 0, 1);
static const glm::vec3 dummy(0, 0, 0) ;


glow::ref_ptr<glow::Buffer> VoxelMesh::s_vertexBuffer = nullptr;

void VoxelMesh::initBuffer() {

    glow::Array<glm::vec3> array{
          rub, dummy
        , lub, dummy
        , rlb, back
        , llb, back
        , llf, bottom
        , lub, left
        , luf, left
        , rub, top
        , ruf, top
        , rlb, right
        , rlf, right
        , llf, bottom
        , ruf, front
        , luf, front
    };

    s_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    s_vertexBuffer->setData(array);
}

void VoxelMesh::tearDown() {
    s_vertexBuffer = nullptr;
}

void VoxelMesh::setupVertexAttribute(glow::ref_ptr<glow::Program> program, glow::ref_ptr<glow::VertexArrayObject> vao, const std::string& name, GLboolean normalised, int bindingNum, GLint offset) {
    glow::VertexAttributeBinding* binding = vao->binding(bindingNum);
    GLint location = program->getAttributeLocation(name);
    assert(location >= 0);

    binding->setAttribute(location);
    binding->setBuffer(vertexBuffer(), 0, sizeof(glm::vec3) * 2);
    binding->setFormat(3, GL_FLOAT, normalised, offset);

    vao->enable(location);
}

glow::ref_ptr<glow::Buffer> VoxelMesh::vertexBuffer() {
    if (!s_vertexBuffer) {
        initBuffer();
    }
    return s_vertexBuffer;
}

void VoxelMesh::bindTo(
    glow::ref_ptr<glow::Program> program,
    glow::ref_ptr<glow::VertexArrayObject> vao,
    int bindingIndex)
{
    setupVertexAttribute(program, vao, "v_vertex", GL_FALSE, bindingIndex + 0, 0);
    setupVertexAttribute(program, vao, "v_normal", GL_TRUE,  bindingIndex + 1, sizeof(glm::vec3));
}

