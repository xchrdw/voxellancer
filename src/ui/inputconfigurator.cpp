#include "inputconfigurator.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glow/logging.hpp>

#include "ui/hud/hud.h"
#include "inputhandler.h"


InputConfigurator::InputConfigurator(std::vector<ActionKeyMapping*>* actions, SecondaryInputValues *secondaryInputValues, Property<float>* deadzone, HUD* hud):
    m_hud(hud),
    m_actions(actions),
    m_secondaryInputValues(secondaryInputValues)
{
    prop_deadzoneGamepad = deadzone;
    m_primaryConfigurationState = -1;
    m_secondaryConfigurationState = -1;
}

bool InputConfigurator::setActionInputMapping(ActionKeyMapping* action, InputClass inputClass) {
    if (isLastInputValid(inputClass)) {
        action->setMapping(lastInput(inputClass), inputClass);
        setLastInput(InputMapping(), inputClass);
        return true;
    }
    return false;
}

bool InputConfigurator::isKeyPressed(InputClass inputClass) {
    if (inputClass == InputClass::Primary) {
        return lastInput(inputClass).type() != InputType::None;
    }
    else {
        for (int i = 0; i < m_secondaryInputValues->buttonCnt; i++) { // get pushed button
            if (m_secondaryInputValues->buttonValues[i] == GLFW_PRESS) {
                return true;
            }
        }
        for (int i = 0; i < m_secondaryInputValues->axisCnt; i++) { // get pushed axes
            if (glm::abs(m_secondaryInputValues->axisValues[i] - m_idleValues[i]) > *prop_deadzoneGamepad) {
                return true;
            }
        }
        return false;
    }
}

bool InputConfigurator::isLastInputValid(InputClass inputClass) {
    if (inputClass == InputClass::Primary) {
        return lastInput(inputClass).type() != InputType::None;
    } else {
        for (int i = 0; i < m_secondaryInputValues->buttonCnt; i++) { // get pushed button
            if (m_secondaryInputValues->buttonValues[i] == GLFW_PRESS) {
                lastInput(inputClass) = InputMapping(InputType::GamePadKey, i, 1, 0.0f);
                return true;
            }
        }
        for (int i = 0; i < m_secondaryInputValues->axisCnt; i++) { // get pushed axes
            if (glm::abs(m_secondaryInputValues->axisValues[i] - m_idleValues[i]) > *prop_deadzoneGamepad) {
                // greater maxValue for same axes
                if (lastInput(inputClass).index() == i) {
                    if (glm::abs(lastInput(inputClass).maxValue() - m_idleValues[i]) <= glm::abs(m_secondaryInputValues->axisValues[i] - m_idleValues[i])) {
                        setLastInput(InputMapping(InputType::GamePadAxis, i, m_secondaryInputValues->axisValues[i], m_idleValues[i]), inputClass);
                        return false;
                    } else {
                        return true;
                    }
                } else {
                    setLastInput(InputMapping(InputType::GamePadAxis, i, m_secondaryInputValues->axisValues[i], m_idleValues[i]), inputClass);
                    return false;
                }
            }
        }
        return false;
    }
}

bool InputConfigurator::isConfiguring() {
    return m_primaryConfigurationState >= 0 || m_secondaryConfigurationState >= 0;
}

void InputConfigurator::startConfiguration(InputClass inputClass) {
    if (inputClass == InputClass::Primary) {
        glow::info("Starting configuration for primary input device (keyboard), Please follow the instructions");
    } else {
        glow::info("Starting configuration for secondary input device (gamepad/Joystick), Please follow the instructions");
        m_idleValues.resize(m_secondaryInputValues->axisCnt);
        for(int a = 0; a < m_secondaryInputValues->axisCnt; a++) {
            m_idleValues[a] = m_secondaryInputValues->axisValues[a];
        }
    }
    setConfigurationState(0, inputClass);
    m_displayedInstructions = false;
    m_displayedKeyPressedWarning = false;
    m_beginningKeyConfiguration = true;
}

void InputConfigurator::update() {
    updateConfiguration(InputClass::Primary);
    updateConfiguration(InputClass::Secondary);
}

void InputConfigurator::updateConfiguration(InputClass inputClass) {
    if (configurationState(inputClass) >= 0) {
        setupControls(inputClass);
    }
}

void InputConfigurator::setupControls(InputClass inputClass) {
    if (!m_displayedInstructions) {
        glow::info("Please press Key for action: %;", m_actions->at(m_primaryConfigurationState)->name());
        m_displayedInstructions = true;
    }
    if (m_beginningKeyConfiguration) {
        if (isKeyPressed(inputClass)) {
            if (!m_displayedKeyPressedWarning) {
                glow::info("Please release all buttons before setting a new key mapping");
                m_displayedKeyPressedWarning = true;
            }
            return;
        } else {
            m_beginningKeyConfiguration = false;
        }
    }
    if (!isLastInputValid(inputClass)) {
        return;
    }
    m_actions->at(configurationState(inputClass))->setMapping(lastInput(inputClass), inputClass);
    setLastInput(InputMapping(), inputClass);
    incrementConfigurationState(inputClass);
    if (configurationState(inputClass) >= m_actions->size()) {
        glow::info("Joystick setup complete");
        setConfigurationState(-1, inputClass);
    }
    m_beginningKeyConfiguration = true;
    m_displayedKeyPressedWarning = false;
    m_displayedInstructions = false;
}

void InputConfigurator::setActions(std::vector<ActionKeyMapping*>* m_actions) {
    this->m_actions = m_actions;
}

void InputConfigurator::setSecondaryInputValues(SecondaryInputValues* values) {
    m_secondaryInputValues = values;
}

void InputConfigurator::setLastInput(InputMapping lastInput, InputClass inputClass) {
    if (inputClass == InputClass::Primary) {
        lastPrimaryInput = lastInput;
    } else {
        lastSecondaryInput = lastInput;
    }
}

InputMapping InputConfigurator::lastInput(InputClass inputClass) {
    if (inputClass == InputClass::Primary) {
        return lastPrimaryInput;
    } else {
        return lastSecondaryInput;
    }
}

int InputConfigurator::configurationState(InputClass inputClass) {
    if (inputClass == InputClass::Primary) {
        return m_primaryConfigurationState;
    } else {
        return m_secondaryConfigurationState;
    }
}

void InputConfigurator::incrementConfigurationState(InputClass inputClass) {
    if (inputClass == InputClass::Primary) {
        m_primaryConfigurationState++;
    } else {
        m_secondaryConfigurationState++;
    }
}

void InputConfigurator::setConfigurationState(int state, InputClass inputClass) {
    if (inputClass == InputClass::Primary) {
        m_primaryConfigurationState = state;
    } else {
        m_secondaryConfigurationState = state;
    }
}