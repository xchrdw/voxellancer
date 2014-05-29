#include "nonplayercharacter.h"

#include "ai/aitask.h"


NonPlayerCharacter::NonPlayerCharacter() = default;

NonPlayerCharacter::~NonPlayerCharacter() = default;

void NonPlayerCharacter::update(float deltaSec) {
    if (m_task) {
        m_task->update(deltaSec);
    }
}

