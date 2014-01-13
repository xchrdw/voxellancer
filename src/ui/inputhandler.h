#pragma once

#include <GL/glew.h>
#include <vector>

#include <GLFW/glfw3.h>

#include "ui/inputconfigurator.h"
#include "property/propertymanager.h"
#include "worldobject/ship.h"
#include "ui/targeter.h"

class WorldObject;
class InputConfigurator;

struct ActionKeyMapping {
    Property<InputMapping> primaryMapping;
    Property<InputMapping> secondaryMapping;
    bool toggleAction;
    bool toggleStatus;
    std::string name;

    ActionKeyMapping(char* primary, char* secondary, std::string name) :
        primaryMapping(primary),
        secondaryMapping(secondary),
        toggleAction(false),
        toggleStatus(false),
        name(name)
    {};

    ActionKeyMapping(char* primary, char* secondary, std::string name, bool toggleAction) :
        primaryMapping(primary),
        secondaryMapping(secondary),
        toggleAction(toggleAction),
        toggleStatus(false),
        name(name)
    {};
};

struct SecondaryInputValues {
    int buttonCnt, axisCnt;
    const unsigned char *buttonValues;
    const float *axisValues;

    SecondaryInputValues(){
        buttonCnt = 0;
        axisCnt = 0;
        buttonValues = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCnt);
        axisValues = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axisCnt);
    }
};

class InputHandler {

public:
    InputHandler(GLFWwindow *window, Camera *camera);
    InputHandler(GLFWwindow *window, Player *player, Camera *camera);
	virtual ~InputHandler();

	void resizeEvent(const unsigned int width, const unsigned int height);
	void keyCallback(int key, int scancode, int action, int mods);
	void update(float delta_sec);

protected:
    GLFWwindow *m_window;
    Camera* m_camera;
    Player* m_player;
    Targeter* m_targeter;
    InputConfigurator* m_inputConfigurator;
    SecondaryInputValues m_secondaryInputValues;
    std::vector<ActionKeyMapping*> m_actions;

    void toggleControls();
    void handleUpdate();
    void handleMouseUpdate();

    void handleFireActions();
    void handleMoveActions();
    void handleRotateActions();
    void handleTargetSelectActions();

    float getInputValue(ActionKeyMapping* action);
    float getInputValue(InputMapping mapping);

    void addActionsToVector();

    void setupJoystickControls();
    int joystickSetupState;

    void retrieveInputValues();

    bool m_mouseControl;
    int m_windowWidth, m_windowHeight;
    int m_cursorMaxDistance;
    int m_lastfocus;


    Property<float> prop_deadzoneMouse;
    Property<float> prop_deadzoneGamepad;


    ActionKeyMapping fireAction;
    ActionKeyMapping rocketAction;

    ActionKeyMapping moveLeftAction;
    ActionKeyMapping moveRightAction;
    ActionKeyMapping moveForwardAction;
    ActionKeyMapping moveBackwardAction;

    ActionKeyMapping rotateLeftAction;
    ActionKeyMapping rotateRightAction;
    ActionKeyMapping rotateUpAction;
    ActionKeyMapping rotateDownAction;
    ActionKeyMapping rotateClockwiseAction;
    ActionKeyMapping rotateCClockwiseAction;

    ActionKeyMapping selectNextAction;
    ActionKeyMapping selectPreviousAction;

};
