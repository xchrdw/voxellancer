#include "boardcomputer.h"

#include <cmath>

#include <glm/gtc/quaternion.hpp>

#include "worldobject/ship.h"
#include "utils/randvec.h"
#include "utils/geometryhelper.h"


static const float s_minActDistance = 0.1f;
static const float s_minActAngle = glm::radians(1.0f);


BoardComputer::BoardComputer(Ship& ship) :
    m_ship(ship)
{
}

void BoardComputer::moveTo(const glm::vec3& position) {
    glm::vec3 projectedPosition = m_ship.physics().projectedTransformIn(1.0f).position();

    glm::vec3 delta = position - projectedPosition;
    glm::vec3 direction = glm::inverse(m_ship.transform().orientation()) * glm::normalize(delta);
    float distance = glm::length(delta);

    if (distance > s_minActDistance) {
        m_ship.accelerate(direction);
    }
}

void BoardComputer::rotateTo(const glm::vec3& position, const glm::vec3& up) {
    float minDelta = glm::radians(5.0f);
    glm::quat projectedOrientation = glm::inverse(m_ship.transform().orientation()) * m_ship.physics().projectedTransformIn(1.0f).orientation();

    glm::vec3 shipDirection = projectedOrientation * glm::vec3(0, 0, -1);
    glm::vec3 targetDirection = glm::inverse(m_ship.transform().orientation()) * glm::normalize(position - m_ship.transform().position());
    glm::quat rotation = GeometryHelper::quatFrom(shipDirection, targetDirection);

    if (up != glm::vec3(0, 0, 0)){
        glm::vec3 upDirection = glm::vec3(0, 1, 0);
        glm::vec3 newUpDirection = glm::inverse(m_ship.transform().orientation()) * glm::normalize(up);
        glm::quat upRotation = GeometryHelper::quatFrom(upDirection, newUpDirection);
        rotation = upRotation * rotation;
    } else {
        //make it look naturally, e.g. up is to the "inside" of the rotation
        if(glm::abs(glm::angle(rotation)) > glm::radians(20.0f)) {
            glm::vec3 upDirection = glm::vec3(0, 1, 0);
            glm::vec3 newUpDirection = glm::vec3(0, 0, 1) + (rotation * glm::vec3(0, 0, -1));
            glm::quat upRotation = GeometryHelper::quatFrom(upDirection, newUpDirection);
            rotation = upRotation * rotation;
        }
    }

    if (glm::abs(glm::angle(rotation)) > s_minActAngle) {
        glm::vec3 euler = glm::eulerAngles(rotation);
        m_ship.accelerateAngular(glm::normalize(euler));
    }
}

void BoardComputer::shootBullet(const std::list<std::shared_ptr<WorldObjectHandle>>& targets) {
    float max_angle = glm::radians(45.0f);

    for (auto targetHandle : targets) {
        if (WorldObject* target = targetHandle->get()) {
            glm::vec3 shipDirection = m_ship.transform().orientation() * glm::vec3(0, 0, -1);
            glm::vec3 targetDirection = target->transform().position() - m_ship.transform().position();
            float angle = GeometryHelper::angleBetween(shipDirection, targetDirection);
            if (glm::abs(angle) < max_angle) {
                glm::vec3 offset = RandVec3::rand(0, 1) * glm::length(targetDirection) / 30.0f;
                m_ship.fireAtPoint(target->transform().position() + offset);
                break;
            }
        }
    }
}

void BoardComputer::shootRockets(std::shared_ptr<WorldObjectHandle> target) {
    if (target->get()) {
        m_ship.setTargetObject(target->get());
        m_ship.fireAtObject();
    }
}
