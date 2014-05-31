#pragma once

#include <map>
#include <list>
#include <string>

#include "util/observable.h"


class WorldObjectComponents;

/**
 * Base class for everything on a worldobject that behaves like a slot
 * that can be (or cannot) be equipped with equipment
 */
class WorldObjectSlot : public Observable {
public:
    WorldObjectSlot(WorldObjectComponents* components, int group);
    virtual ~WorldObjectSlot();

    std::list<std::string> mountables() const;

    bool mountable(const std::string& name) const;
    void setMountable(const std::string& name, bool mountable);

    WorldObjectComponents* components();
    const WorldObjectComponents* components() const;

    int group() const;


protected:
    WorldObjectComponents* m_components;
    std::map<std::string, bool> m_mountables;
    int m_group;
};

