#pragma once

#include <memory>
#include <string>

#include "hudget.h"
#include "ui/voxelfontconstants.h"

class TextFieldHudget;
class VoxelFont;

class TextFieldHudgetVoxels{
public:
    TextFieldHudgetVoxels(TextFieldHudget* textFieldHudget, const glm::vec3& direction, float scale = 0.5f, const std::string& text = "", FontSize fontSize = FontSize::SIZE5x7);

    void setText(const std::string& text);


    virtual void draw();

    virtual bool isAt(const Ray& ray) const;

    float width();
    float height();
    float scale();

protected:

    Hudget* m_hudget;
	
    glm::vec3 m_direction;
    glm::vec3 worldPosition() const;
    glm::quat worldOrientation() const;

    FontSize m_fontSize;
    VoxelFont* m_voxelFont;
	
    float m_width, m_height, m_scale;
    float m_offset;

    const glm::vec3 offsetToCenter(bool upper, bool left) const;

    const glm::vec3 upperLeft() const;
    const glm::vec3 lowerLeft() const;
    const glm::vec3 upperRight() const;
    const glm::vec3 lowerRight() const;
};

