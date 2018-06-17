/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include <engine/components/HoldComponent.hpp>
#include <engine/components/ItemComponent.hpp>
#include <engine/components/CameraComponent.hpp>
#include "engine/components/PhysicsComponent.hpp"
#include "engine/components/AnimationComponent.hpp"
#include "engine/components/TextComponent.hpp"
#include "engine/components/TimeoutComponent.hpp"
#include "engine/components/TransformComponent.hpp"
#include "game/components/MasterComponent.hpp"
#include "engine/systems/PhysicsSystem.hpp"
#include "game/components/MasterComponent.hpp"
#include "game/components/PlayerComponent.hpp"
#include "PlayerSystem.hpp"

float const worms::PlayerSystem::_CameraSpeed = 5;
irr::core::vector3df const worms::PlayerSystem::_CameraOffset = engine::CameraComponent::Coords(0.f, 5.f, -15.f);

void
worms::PlayerSystem::update(engine::Scene& scene, float tick)
{
	engine::Entities& entities = scene.getEntities();

	entities.each<PlayerComponent, engine::PhysicsComponent, engine::AnimationComponent, engine::HoldComponent>([&entities, tick](engine::Entity const& e, auto& pl, auto& ph, auto& a, auto& hc) {
		if (engine::PhysicsSystem::isGrounded(entities, e)) {
			if (!a.playOnce)
				a.currentState = (ph.move.X == 0 ? getState("idle", hc) : getState("run", hc));
			a.playOnce = false;
		}

		entities.each<MasterComponent>([&](auto const&, auto& m) {
			if (m.players[m.currentPlayer] == e.getId()) {
				entities.each<engine::CameraComponent>([e, tick](engine::Entity const& eCamera, auto& tCamera) {
					irr::core::vector3df const& oldPosition = tCamera.node->getPosition();
					irr::core::vector3df const& newPosition = e.get<engine::TransformComponent>().position + _CameraOffset;
					irr::core::vector3df const& oldTarget = tCamera.node->getTarget();
					irr::core::vector3df const& newTarget = e.get<engine::TransformComponent>().position;
					float ratio = tick * _CameraSpeed;

					tCamera.node->setPosition((oldPosition * (1 - ratio) + newPosition * ratio));
					tCamera.node->setTarget((oldTarget * (1 - ratio) + newTarget * ratio));
				});
			}
		});
	});

	entities.each<engine::TransformComponent, PlayerComponent>([&](auto const& e, auto& t, auto& p) {
		_videoDriver->draw3DLine({t.position.X - .1f, t.position.Y + 2, 0}, {static_cast<float>(t.position.X - .1f + p.hp / 100.f), t.position.Y + 2, 0}, irr::video::SColor(255, 255, 0, 0));
	});

	entities.withTag("timer", [](engine::Entity const& timer) {
		auto newtime = std::to_wstring(engine::TimeoutComponent::Constraint::Pool::instance().get(0).back().remaining);
		timer.get<engine::TextComponent>().node->setText(newtime.substr(0, newtime.find('.')).c_str());
	});
}

std::string
worms::PlayerSystem::getState(std::string const& state, engine::HoldComponent const& hc)
{
	if (hc.current == -1) {
		return state;
	} else if (hc.items[hc.current].get<engine::ItemComponent>().heavy) {
		return state + "HoldHeavy";
	}

	return state;
}
