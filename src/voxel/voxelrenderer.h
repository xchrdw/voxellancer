#pragma once
#include <glow/ref_ptr.h>

#include "voxelcluster.h"


namespace glow {
	class Texture;
	class Program;
	class VertexArrayObject;
	class Buffer;
};

class Camera;

class VoxelRenderer {
public:
    VoxelRenderer();

	void prepareDraw(Camera * camera, bool withBorder = true);
    void draw(VoxelCluster * cluster);
    void afterDraw();
  
private:
    void createAndSetupShaders();
    void createAndSetupGeometry();

    glow::ref_ptr<glow::Texture> m_texture;
	glow::ref_ptr<glow::Program> m_shaderProgram;
	glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
	glow::ref_ptr<glow::Buffer> m_vertexBuffer;
};