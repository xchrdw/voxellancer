#include "cameradolly.h"

#include "worldobject/worldobject.h"


CameraDolly::CameraDolly():
    InertiaFollower(10.0f, 10.0f),
    m_cameraHead(this)
{
}

const CameraHead& CameraDolly::cameraHead() const {
    return m_cameraHead;
}

void CameraDolly::setHeadOrientation(const glm::quat& orientation) {
    m_cameraHead.setRelativeOrientation(orientation);
}

void CameraDolly::followWorldObject(WorldObject* followWorldObject) {
    m_followHelper.setTarget(followWorldObject);
}

void CameraDolly::update(float deltaSec) {
    WorldObject* followWorldObject = m_followHelper.target();

    if(followWorldObject) {
        follow(m_followHelper.followPosition(), followWorldObject->transform().orientation(), deltaSec);
    }
}

