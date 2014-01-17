#pragma once

#include <vector>

#include "input/inputmapping.h"
#include "property/property.h"

#include "inputhandler.h"

struct ActionKeyMapping;
struct SecondaryInputValues;

class HUD;

class InputConfigurator
{
public:
    InputConfigurator(std::vector<ActionKeyMapping*>* actions, SecondaryInputValues *secondaryInputValues, Property<float>* deadzone, HUD* hud);
    void startConfiguration(bool primary);
    bool isConfiguring();
    void update();

    void setActions(std::vector<ActionKeyMapping*>* actions);

    void setSecondaryInputValues(SecondaryInputValues* values);

    void setLastPrimaryInput(InputMapping lastInput);
    void setLastSecondaryInput(InputMapping lastInput);


private:
    std::vector<ActionKeyMapping*>* actions;
    SecondaryInputValues *secondaryInputValues;

    HUD* hud;

    Property<float>* prop_deadzoneMouse;
    Property<float>* prop_deadzoneGamepad;

    bool setActionInputMapping(ActionKeyMapping* action, bool primary);
    bool isLastPrimaryInputValid();
    bool isLastSecondaryInputValid();

    bool isSecondaryInput();
    bool isPrimaryInput();
    
    void setupPrimaryControls();
    void setupSecondaryControls();

    InputMapping lastPrimaryInput;
    InputMapping lastSecondaryInput;

    int secondaryConfigurationState;
    int primaryConfigurationState;

    bool beginningKeyConfiguration = true;
    bool displayedKeyPressedWarning = false;
    bool displayedInstructions = false;
};
