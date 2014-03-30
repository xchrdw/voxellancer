#pragma once

#include <memory>
#include <unordered_set>


class EventPoller;
class FactionMatrix;
class God;
class Player;
class Ship;
class Skybox;
class ScriptEngine;
class VoxelParticleEngine;
class WorldObject;
class WorldLogic;
class WorldTree;
class TextFieldHudget;
class HUD;

class World {
public:
    World();
    virtual ~World();

    Player& player();
    void setPlayer(Player& player);

    Skybox& skybox();
    WorldLogic& worldLogic();
    God& god();
    WorldTree& worldTree();
    ScriptEngine& scriptEngine();
    VoxelParticleEngine& particleEngine();
    FactionMatrix& factionMatrix();
    EventPoller& eventPoller();

    std::unordered_set<WorldObject*>& worldObjects();
    std::unordered_set<Ship*>& ships();

    void printStatus();

    void update(float deltaSecs);

    float deltaSec() const;

    static World *instance();

    void showText(std::string text, HUD* hud, float lifeTime = 2.0f);

    static void reset(bool showWarning=true);

protected:
    friend class God;

    void addWorldObject(WorldObject* worldObject);
    void removeWorldObject(WorldObject* worldObject);

protected:
    static World *s_instance;

    float m_deltaSec;
    Player* m_player;

    std::unique_ptr<Skybox> m_skybox;
    std::unique_ptr<WorldTree> m_worldTree;
    std::unique_ptr<WorldLogic> m_worldLogic;
    std::unique_ptr<God> m_god;
    std::unique_ptr<ScriptEngine> m_scriptEngine;
    std::unique_ptr<VoxelParticleEngine> m_particleEngine;
    std::unique_ptr<FactionMatrix> m_factionMatrix;
    std::unique_ptr<EventPoller> m_eventPoller;

    std::unique_ptr<TextFieldHudget> m_textHudget;
    float m_textLifeTime;
    float m_textTimer;
    

    std::unordered_set<WorldObject*> m_worldObjects;
    std::unordered_set<Ship*> m_ships;

};

