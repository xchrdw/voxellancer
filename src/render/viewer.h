#pragma once

#include "scene.h"
#include "view.h"


class Viewer {
public:
    Viewer();

    void setScene(Scene* scene);

    void setCameraHead(CameraHead* cameraHead);

    void toMonoView();
    void toStereoView();

    void draw();


protected:
    Scene* m_scene;
    View* m_view;
    CameraHead* m_cameraHead;
};

