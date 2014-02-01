#include <glm/glm.hpp>

#include "property/property.h"

#include "worldobject/components/weapon.h"

#include "bullet.h"


class Gun: public Weapon {
public:
    Gun();

    virtual WeaponAimType aimType() const override;
    virtual float estimatedRange() const override;
    virtual float cooldownTime() const override;

    virtual void shootAtPoint(const glm::vec3& point) override;

    virtual void update(float deltaSec) override;


protected:
    Property<float> m_coolDownTime;
    Property<float> m_bulletSpeed;
    Property<float> m_bulletLifetime;
};

