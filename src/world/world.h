#pragma once

#include <list>
#include <memory>
#include <unordered_set>

#include <glow/ref_ptr.h>
#include "utils/component.h"


class FactionMatrix;
class God;
class Player;
class Ship;
class Skybox;
class ScriptEngine;
class VoxelParticleEngine;
class WorldObject;
class SectorLogic;
class UniverseElement;
class WorldTree;

class World {
public:
    World();
    virtual ~World();

    Player& player();
    Skybox& skybox();
    SectorLogic& worldLogic();
    God& god();
    WorldTree& worldTree();
    ScriptEngine& scriptEngine();
    VoxelParticleEngine& particleEngine();
    FactionMatrix& factionMatrix();

    std::unordered_set<WorldObject*>& worldObjects();
    std::unordered_set<Ship*>& ships();

    void printStatus();

    void update(float deltaSecs);

    float deltaSec() const;

    static World* instance();

    static void reset(bool showWarning = true);

    void addElement(UniverseElement* element);
    void removeElement(UniverseElement* element);


protected:
    friend class God;

    void addWorldObject(WorldObject* worldObject);
    void removeWorldObject(WorldObject* worldObject);


protected:
    static World* s_instance;

    float m_deltaSec;

    Component<Player> m_player;
    Component<ScriptEngine> m_scriptEngine;
    Component<Skybox> m_skybox;
    Component<WorldTree> m_worldTree;
    Component<SectorLogic> m_worldLogic;
    Component<God> m_god;
    Component<VoxelParticleEngine> m_particleEngine;
    Component<FactionMatrix> m_factionMatrix;
    std::list<glow::ref_ptr<UniverseElement>> m_elements;
    std::unordered_set<UniverseElement*> m_scheduledRemovals;

    std::unordered_set<WorldObject*> m_worldObjects;
    std::unordered_set<Ship*> m_ships;
};

