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
#include "engine/components/ParticlesComponent.hpp"
#include "engine/components/LightComponent.hpp"
#include "engine/components/ProgressBarComponent.hpp"

engine::DisplaySystem::DisplaySystem(engine::Game& game) : _game(game)
{
	_videoDriver = _game.device()->getVideoDriver();
	_sceneManager = _game.device()->getSceneManager();
	_guiEnv = _game.device()->getGUIEnvironment();
	_sceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 30, -200), irr::core::vector3df(0, 5, 0));
}

void
engine::DisplaySystem::update(Scene& scene, float)
{
	Entities& entities = scene.getEntities();

	auto transformNode = [](auto const& e, auto& t, auto& component) -> void {
		component.node->setPosition(t.position + t.magicPosition + (t.offset * t.scale));
		component.node->setRotation(t.rotation + t.offsetRotation);
		component.node->setScale(t.scale);
	};

	entities.each<TransformComponent, IrrlichtComponent>(transformNode);
	entities.each<TransformComponent, LightComponent>(transformNode);
	entities.each<TransformComponent, ParticlesComponent>([&transformNode](auto const& e, auto& t, auto& particles) {
		for (auto& particle : particles) {
			transformNode(e, t, particle);
		}
	});

    entities.each<TransformComponent, AnimationComponent>([](auto const& e, auto& t, auto& a) {
        t.rotation.Y = t.direction ? 0 : 180;
    });

	entities.each<TransformComponent, IrrlichtComponent, ProgressBarComponent>([&transformNode](auto const& e, auto& t, auto& i, auto& p) {
		auto const& t2 = engine::TransformComponent::Constraint::Pool::instance().get(e.getParentId());

		t.position = t2.position;
		t.position.Y += 10;
		transformNode(e, t, i);
	});

	entities.each<AnimationComponent, IrrlichtComponent>([](auto const& e, auto& a, auto& i) {
		AnimationBoundaries const& boundaries = a.states.at(a.currentState);

		if (boundaries.from != i.node->getStartFrame() || boundaries.to != i.node->getEndFrame()) {
			i.node->setFrameLoop(boundaries.from, boundaries.to);
			i.node->setLoopMode(true);
		}

		if (a.playOnce && i.node->getEndFrame() - i.node->getFrameNr() < 1.5) {
			if (a.nextState != "") {
				a.currentState = a.nextState;
				a.nextState = "";
				a.playOnce = false;
			} else {
				i.node->setLoopMode(false);
			}
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
            auto wSegment = engine::Segment3D {
                (segment.p1* t.scale + t.position),
                (segment.p2 * t.scale + t.position)
            };

            _videoDriver->draw3DLine(wSegment.p1, wSegment.p2, irr::video::SColor(255, 255, 0, 0));
        }
    });

//    _videoDriver->draw3DLine({-100, 0, 0}, {100, 0, 0}, irr::video::SColor(255, 255, 0, 0));
//    _videoDriver->draw3DLine({0, -100, 0}, {0, 100, 0}, irr::video::SColor(255, 0, 255, 0));
//    _videoDriver->draw3DLine({0, 0, -100}, {0, 0, 100}, irr::video::SColor(255, 0, 0, 255));
}

engine::DisplaySystem::~DisplaySystem()
{}
