//
//  BattleSceneModel.hpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#pragma once

#include <iostream>
#include "engine/core/Game.hpp"
#include "engine/components/LightComponent.hpp"
#include "engine/components/ComponentFilter.hpp"
#include "engine/components/IrrlichtComponent.hpp"
#include "engine/components/HitboxComponent.hpp"
#include "engine/components/TransformComponent.hpp"
#include "engine/components/TagComponent.hpp"
#include "engine/components/CameraComponent.hpp"
#include "engine/components/PhysicsComponent.hpp"
#include "engine/components/AnimationComponent.hpp"
#include "engine/systems/PhysicsSystem.hpp"
#include "engine/core/Scene.hpp"
#include "engine/core/Event.hpp"
#include "game/events/Vector.hpp"

namespace worms { namespace scene {

	static const auto battle = [](engine::Game& game, engine::Scene& scene) {
		scene.registerEntityModel("camera", [&](engine::Entity const& entity) {
			auto& cameraComponent = entity.set<engine::CameraComponent>(game.device(),
										engine::CameraComponent::Coords {0.f, 0.f, -10.f}, engine::CameraComponent::Coords {0, 0, 0}
			);

            entity.set<engine::TransformComponent>();


			scene.registerEvent<Vector3f>("set camera position", [&](auto const& position) {
				cameraComponent.node->setPosition(position);
				return 0;
			});

			scene.registerEvent<Vector3f>("set camera lookat", [&](auto const& position) {
				cameraComponent.node->setTarget(position);
				return 0;
			});

			scene.registerEvent<Vector3f>("move camera", [&](auto const& offset) {
				cameraComponent.node->setPosition(cameraComponent.node->getPosition() + offset);
				cameraComponent.node->setTarget(cameraComponent.node->getTarget() + offset);
				return 0;
			});
		});

		// scene.registerEntityModel("map", [&](engine::Entity const& entity) {
		// 	auto& IrrlichtComponent = entity.set<engine::IrrlichtComponent>(&game, "obj/map.obj");
		// 	IrrlichtComponent.node->setPosition(irr::core::vector3df {0.f, 0.f, 0.f});
		// 	IrrlichtComponent.node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		// 	IrrlichtComponent.node->setMD2Animation(irr::scene::EMAT_STAND);
		// 	IrrlichtComponent.node->setMaterialTexture(0, game.textureManager.get("texture/map.png"));
        //
		// 	entity.get<engine::IrrlichtComponent,
		// 		engine::IrrlichtComponent>([](engine::IrrlichtComponent const& irrlichtComponent,
		// 					    engine::IrrlichtComponent const& irrlichtComponent2) {
		// 	});
		// });

		scene.registerEntityModel("block", [&](engine::Entity const& entity) {
            entity.set<engine::IrrlichtComponent>(&game, "obj/block.obj");
			entity.set<engine::TagComponent>(std::string("map"));

            auto& transformComponent = entity.set<engine::TransformComponent>();
            transformComponent.position = {0.f, 0.f, 0.f};

			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-50 -10, -50 20, -28 20, -28 4, -20 1, -10 1, 1 2, 2 8, 5 8, 5 -10, 1 -10)");
            hitboxComponent.rebound = 0.8;
            hitboxComponent.hasDebugMode = true;

		});

        scene.registerEntityModel("worm", [&](engine::Entity const& entity) {
			entity.set<engine::IrrlichtComponent>(&game, "obj/worm.obj", "texture/worm.png");

            std::cout << "worms id: " << entity.getId() << std::endl;

            auto& physicsComponent = entity.set<engine::PhysicsComponent>();
            auto& transformComponent = entity.set<engine::TransformComponent>();
            transformComponent.scale = {.5f, .5f, .5f};
            transformComponent.position = {0.f, 25.f, 0.f};

			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-1 0, -1 4, 1 4, 1 0)");
            hitboxComponent.hasDebugMode = true;
			hitboxComponent.rebound = 0.1f;

			// @Synced -> std::string
			scene.registerEvent<std::string>("jump player", [entity, &scene, &physicsComponent](std::string const& jump) {
                if (engine::PhysicsSystem::isGrounded(scene.getEntities(), entity)) {
                    physicsComponent.velocity += (Vector2f) jump;
                }

				return 0;
			});

			// @Synced -> std::string
			scene.registerEvent<std::string>("move player", [&](std::string const& move) {
                physicsComponent.move = (Vector2f) move;
				return 0;
			});
		});

		scene.registerEntityModel("light", [&](engine::Entity const& entity) {
			entity.set<engine::LightComponent>(game.device(), irr::core::vector3df(0, 500, 50),
							   irr::video::SColorf(0.0f, 0.0f, 0.0f), 1000);
		});

		scene.registerEvent<engine::GenericEvent>("spawn worm", [&](engine::GenericEvent const&) {
			scene.spawnEntity("worm");
			return 0;
		});

		game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_Q, "move player", Vector2f(-10.f, 0.f), engine::EVT_SYNCED);
		game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_Q, "move player", Vector2f(0.f, 0.f), engine::EVT_RELEASE | engine::EVT_SYNCED);
		game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_D, "move player", Vector2f(10.f, 0.f), engine::EVT_SYNCED);
		game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_D, "move player", Vector2f(0.f, 0.f), engine::EVT_RELEASE | engine::EVT_SYNCED);
		game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_SPACE, "jump player", Vector2f(0.f, 100.f), engine::EVT_SYNCED);

		game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_RIGHT, "move camera", Vector3f(-1.f, 0.f, 0.f));
		game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_LEFT,  "move camera", Vector3f(1.f, 0.f, 0.f));
		game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_UP,    "move camera", Vector3f(0.f, 1.f, 0.f));
		game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_DOWN,  "move camera", Vector3f(0.f, -1.f, 0.f));
		game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_KEY_R, "move camera", Vector3f(0.f, 0.f, 1.f));
		game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_KEY_F, "move camera", Vector3f(0.f, 0.f, -1.f));

		scene.spawnEntity("light");
		scene.spawnEntity("camera");
        scene.spawnEntity("block");
        scene.spawnEntity("worm");
//		scene.spawnEntity("map");
//		scene.spawnEntity("animated");

//		if (!WORMS_IS_SERVER) {
//			scene.synchronizeWith("localhost", game);
//		}
	};
}}
