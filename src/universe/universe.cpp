#include "universe.h"

#include "scripting/scriptengine.h"

#include "player.h"
#include "sector.h"


Universe::Universe() = default;
Universe::~Universe() = default;

Player& Universe::player() {
    return m_player;
}

ScriptEngine& Universe::scriptEngine() {
    return m_scriptEngine;
}

void Universe::addSector(const std::shared_ptr<Sector>& sector) {
    m_sectors.push_back(sector);
}

void Universe::update(float deltaSec) {
    m_player->update(deltaSec);
    m_scriptEngine->update(deltaSec);

    for (std::shared_ptr<Sector>& sector : m_sectors) {
        sector->update(deltaSec);
    }
}

