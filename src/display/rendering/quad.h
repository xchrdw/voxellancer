#pragma once

#include <iostream>

#include <glow/ref_ptr.h>

namespace glow {
    class VertexArrayObject;
    class Buffer;
}

class Camera;

class Quad {
public:
    static const int VERTEX_ATTRIBUTE_LOCATION = 0;

    Quad();

    void draw();

protected:
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
    glow::ref_ptr<glow::Buffer> m_vertexBuffer;

    void initialize();
};
