/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <engine/components/AnimationComponent.hpp>
#include "engine/core/Game.hpp"
#include "engine/systems/DisplaySystem.hpp"
#include "engine/components/HitboxComponent.hpp"
#include "engine/components/TransformComponent.hpp"
#include "engine/components/IrrlichtComponent.hpp"

engine::DisplaySystem::DisplaySystem(engine::Game& game) : _game(game)
{
	_videoDriver = _game.device()->getVideoDriver();
	_sceneManager = _game.device()->getSceneManager();
	_guiEnv = _game.device()->getGUIEnvironment();
	_sceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 30, -200), irr::core::vector3df(0, 5, 0));
}

void
engine::DisplaySystem::update(Scene& scene)
{
	Entities& entities = scene.getEntities();

	_game.lockDevice();
	_game.device()->run();
	_videoDriver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

	entities.each<TransformComponent, IrrlichtComponent>([](auto const& e, auto& t, auto& i) {
		i.node->setPosition(t.position);
		i.node->setRotation(t.rotation);
		i.node->setScale(t.scale);
	});

	entities.each<AnimationComponent, IrrlichtComponent>([](auto const& e, auto& a, auto& i) {
		AnimationBoundaries const& boundaries = a.states.at(a.currentState);

		if (boundaries.from != i.node->getStartFrame() || boundaries.to != i.node->getEndFrame()) {
			i.node->setFrameLoop(boundaries.from, boundaries.to);
		}

		i.node->setAnimationSpeed(a.frameRate);
	});

	_sceneManager->drawAll();
	_guiEnv->drawAll();

    irr::video::SMaterial mtl;
    mtl.Lighting = false;
    _videoDriver->setMaterial(mtl);
    _videoDriver->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());

    entities.each<TransformComponent, IrrlichtComponent, HitboxComponent>([this](auto const& e, auto& t, auto& i, auto& h) {
        if (!h.hasDebugMode) {
            return;
        }
        for (auto& segment : h.segments3D) {
		segment.p1.Z = -1.f;
		segment.p2.Z = -1.f;
            auto wSegment = engine::Segment3D{
                (segment.p1* t.scale + t.position),
                (segment.p2 * t.scale + t.position)
            };

            _videoDriver->draw3DLine(wSegment.p1, wSegment.p2, irr::video::SColor(255, 255, 0, 0));
        }
    });

    // debug: display axis
    _videoDriver->draw3DLine({-100, 0, 0}, {100, 0, 0}, irr::video::SColor(255, 255, 0, 0));
    _videoDriver->draw3DLine({0, -100, 0}, {0, 100, 0}, irr::video::SColor(255, 0, 255, 0));
    _videoDriver->draw3DLine({0, 0, -100}, {0, 0, 100}, irr::video::SColor(255, 0, 0, 255));

	_videoDriver->endScene();
	_game.releaseDevice();
}

engine::DisplaySystem::~DisplaySystem()
{}
