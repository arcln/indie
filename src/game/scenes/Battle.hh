//
//  BattleSceneModel.hpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#pragma once

#include <iostream>
#include <string>
#include "engine/core/Game.hpp"
#include "game/events/Vector.hpp"
#include "engine/components/LightComponent.hpp"
#include "engine/components/IrrlichtComponent.hpp"
#include "engine/components/HitboxComponent.hpp"
#include "engine/components/TransformComponent.hpp"
#include "engine/components/TagComponent.hpp"
#include "engine/components/CameraComponent.hpp"
#include "engine/components/PhysicsComponent.hpp"

namespace worms { namespace scene {

	static const auto battle = [](engine::Game& game, engine::Scene& scene) {

		/********************************************************************\
		|*				  				HELPERS								*|
		\********************************************************************/

		std::vector<engine::Entity> players;

		/********************************************************************\
		|*				  				MODELS								*|
		\********************************************************************/

		scene.registerEntityModel("camera", [&](engine::Entity const& entity) {
			entity.set<engine::TransformComponent>();
			auto& cameraComponent = entity.set<engine::CameraComponent>(
				game.device(), engine::CameraComponent::Coords {0.f, 0.f, -10.f}, engine::CameraComponent::Coords {0, 0, 0}
			);

			scene.registerEvent<Vector3f>("camera.goto", [&](auto const& position) {
				cameraComponent.node->setPosition(position);
				return 0;
			});

			scene.registerEvent<Vector3f>("camera.lookat", [&](auto const& position) {
				cameraComponent.node->setTarget(position);
				return 0;
			});

			scene.registerEvent<Vector3f>("camera.move", [&](auto const& offset) {
				cameraComponent.node->setPosition(cameraComponent.node->getPosition() + offset);
				cameraComponent.node->setTarget(cameraComponent.node->getTarget() + offset);
				return 0;
			});
		});

        scene.registerEntityModel("player", [&](engine::Entity const& entity) {
			entity.set<engine::IrrlichtComponent>(&game, "obj/worm.obj", "texture/worm.png");

            auto& physicsComponent = entity.set<engine::PhysicsComponent>();
            auto& transformComponent = entity.set<engine::TransformComponent>();
            transformComponent.scale = {.5f, .5f, .5f};
            transformComponent.position = {0.f, 25.f, 0.f};

			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-1 0, -1 4, 1 4, 1 0)");
            hitboxComponent.hasDebugMode = true;
			hitboxComponent.rebound = 0.1f;

			scene.registerEvent<std::string>("player.move", [&](std::string const& move) {
				physicsComponent.move = (Vector2f) move;
				return 0;
			});

			scene.registerEvent<std::string>("player.jump", [entity, &scene, &physicsComponent](std::string const& jump) {
                if (engine::PhysicsSystem::isGrounded(scene.getEntities(), entity)) {
                    physicsComponent.velocity += (Vector2f) jump;
                }

				return 0;
			});
		});

		scene.registerEntityModel("block", [&](engine::Entity const& entity) {
			entity.set<engine::IrrlichtComponent>(&game, "obj/block.obj");
			entity.set<engine::TagComponent>(std::string("map"));

			auto& transformComponent = entity.set<engine::TransformComponent>();
			transformComponent.position = {0.f, 0.f, 0.f};

			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-50 -10, -50 20, -28 20, -28 4, -20 1, -10 1, 1 2, 2 8, 5 8, 5 -10, 1 -10)");
			hitboxComponent.rebound = 0.8;
			hitboxComponent.hasDebugMode = true;
		});

		scene.registerEntityModel("light", [&](engine::Entity const& entity) {
			entity.set<engine::LightComponent>(
				game.device(), irr::core::vector3df(0, 500, 50), irr::video::SColorf(0.0f, 0.0f, 0.0f), 1000
			);
		});

		/********************************************************************\
		|*				  		SERVER SYNCED EVENTS						*|
		\********************************************************************/

		game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_Q, "player.move", Vector2f(-10.f, 0.f), engine::EVT_SYNCED);
		game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_Q, "player.move", Vector2f(0.f, 0.f), engine::EVT_SYNCED | engine::EVT_RELEASE);
		game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_D, "player.move", Vector2f(10.f, 0.f), engine::EVT_SYNCED);
		game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_D, "player.move", Vector2f(0.f, 0.f), engine::EVT_SYNCED | engine::EVT_RELEASE);
		game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_SPACE, "player.jump", Vector2f(0.f, 100.f), engine::EVT_SYNCED);

		scene.registerEvent<engine::GenericEvent>("player.spawn", [&](engine::GenericEvent const&) {
			scene.spawnEntity("worm");
			return 0;
		});

		/********************************************************************\
		|*				  		CLIENT ONLY EVENTS							*|
		\********************************************************************/

		game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_RIGHT, "camera.move", Vector3f(-1.f, 0.f, 0.f));
		game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_LEFT,  "camera.move", Vector3f(1.f, 0.f, 0.f));
		game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_UP,    "camera.move", Vector3f(0.f, 1.f, 0.f));
		game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_DOWN,  "camera.move", Vector3f(0.f, -1.f, 0.f));
		game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_KEY_R, "camera.move", Vector3f(0.f, 0.f, 1.f));
		game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_KEY_F, "camera.move", Vector3f(0.f, 0.f, -1.f));

		/********************************************************************\
		|*					  		START ENTITIES							*|
		\********************************************************************/

		scene.spawnEntity("camera");
		scene.spawnEntity("player");
		scene.spawnEntity("block");
		scene.spawnEntity("light");
	};
}}
