#include "gamescene.h"

#include <glow/FrameBufferObject.h>

#include "voxel/voxelrenderer.h"
#include "voxeleffect/voxelparticleworld.h"
#include "utils/hd3000dummy.h"
#include "sound/soundmanager.h"
#include "programs/monoblitprogram.h"
#include "game.h"
#include "rendering/framebuffer.h"
#include "rendering/renderpipeline.h"
#include "rendering/blitter.h"

GameScene::GameScene(Game* game) :
    m_game(game),
    m_voxelRenderer(VoxelRenderer::instance()),
    m_hd3000dummy(new HD3000Dummy()),
    m_soundManager(new SoundManager()),
    m_blitter(new Blitter()),
    m_framebuffer(new FrameBuffer(8)),
    m_renderPipeline(RenderPipeline::getDefault()),
    m_currentOutputBuffer(0) 
{
}

void GameScene::draw(Camera* camera, glow::FrameBufferObject* destination, const glm::ivec2& resolution) {
    m_framebuffer->setResolution(resolution);
    m_framebuffer->clear();

    m_framebuffer->setDrawBuffers({ BufferName::Color, BufferName::NormalZ, BufferName::Emissisiveness });
    drawGame(camera);

    m_renderPipeline->apply(*m_framebuffer);

    m_blitter->setInput({ static_cast<BufferName>(m_currentOutputBuffer) });
    m_blitter->apply(*m_framebuffer, destination);
}

void GameScene::activate() {
    m_soundManager->activate();
}

void GameScene::deactivate() {
    m_soundManager->deactivate();
}

void GameScene::setCameraHead(CameraHead* head) {
    m_head = head;
}

void GameScene::update(float deltaSec) {
    m_soundManager->setListener(m_head->position(), m_head->orientation());
}

void GameScene::setOutputBuffer(int i) {
    m_currentOutputBuffer = i;
}

void GameScene::drawGame(Camera* camera) {
    World::instance()->skybox().draw(camera);

    m_voxelRenderer->prepareDraw(camera);
    for (WorldObject* worldObject : World::instance()->worldObjects()) {
        VoxelRenderer::instance()->draw(worldObject);
    }
    m_game->player().hud().draw();
    m_voxelRenderer->afterDraw();

    World::instance()->voxelParticleWorld().draw(*camera);

    m_hd3000dummy->drawIfActive();
}
