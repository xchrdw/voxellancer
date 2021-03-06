#pragma once

#include "display/scene.h"


class Intro;
class VoxelFont;
class VoxelRenderer;

class IntroScene : public Scene {
public:
    IntroScene(Intro& intro);
    ~IntroScene() override;

    void update(float deltaSec) override;


protected:
    Intro& m_intro;
    std::unique_ptr<VoxelFont> m_font;
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;


    void drawImpl(const Camera& camera) const override;
};

