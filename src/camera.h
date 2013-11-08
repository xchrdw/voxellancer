#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include "worldobject.h"

/* Represents the camera. matrix thus is the view matrix for all other objects */
class Camera : protected WorldObject { //protected so we don't have matrix, because we want view
public:
	Camera();
	virtual ~Camera();

	/* Overwrite WorldObject functions for performance:
	*	WorldObject recalculates the matrix on every read access,
	*	Camera should recalculate on every write acces, as reads are more common */

	void move(glm::vec3 dist);
	void moveTo(glm::vec3 pos);

	void rotateX(float rot);
	void rotateY(float rot);
	void rotateZ(float rot);
	void rotateTo(glm::quat quat);

	const glm::mat4 view();
	const glm::mat4 viewInverted();
	const glm::quat orientation();

	/* Projection from glow::Camera */

	float zNear() const;
	void setZNear(float zNear);
	float zFar() const;
	void setZFar(float zFar);

	float fovy() const;
	void setFovy(float fovy);

	const glm::ivec2 viewport() const;
	void setViewport(const glm::ivec2 & viewport);

	float aspectRatio() const;

	const glm::mat4 projection();

	const glm::mat4 viewProjection();

protected:
	void viewDirty();
	void projectionDirty();

	float m_fovy;
	float m_aspect;
	float m_zNear;
	float m_zFar;

	glm::ivec2 m_viewport;

	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::mat4 m_viewProjection;

};