/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Menu Hh
*/

#pragma once

#include <iostream>
#include <engine/components/LightComponent.hpp>
#include <engine/components/ComponentFilter.hpp>
#include <engine/components/IrrlichtComponent.hpp>
#include "engine/core/Scene.hpp"
#include "engine/core/Event.hpp"
#include "engine/core/Game.hpp"
#include "engine/components/CameraComponent.hpp"
#include "engine/components/ButtonComponent.hpp"
#include "engine/components/ImageComponent.hpp"
#include "engine/menu/classes/parsers/MyScriptParser.hpp"


namespace worms { namespace scene {

	static const auto mainMenu = [](engine::Game& game, engine::Scene& scene) {
		scene.registerEntityModel("camera", [&](engine::Entity const& entity) {
			auto& cameraComponent = entity.set<engine::CameraComponent>(game.device(),
										    engine::CameraComponent::Coords {
											    0.f, 0.f, -10.f},
										    engine::CameraComponent::Coords {0,
														     0,
														     0}
			);

			scene.registerEvent<engine::CameraComponent::Coords>("set camera position", [&](auto const& position) {
				cameraComponent.node->setPosition(position);
				return 0;
			});

			scene.registerEvent<engine::CameraComponent::Coords>("set camera lookat", [&](auto const& position) {
				cameraComponent.node->setTarget(position);
				return 0;
			});
		});

		scene.registerEntityModel("button", [&](engine::Entity const& entity) {
			static irr::s32 id = 0;
			auto& buttonComponent = entity.set<engine::ButtonComponent>(game.device(),
										    irr::core::rect<irr::s32>(10, 10, 200, 200),
										    nullptr,
										    id,
										    nullptr,
										    nullptr
			);
			buttonComponent.node->setUseAlphaChannel(true);

			scene.registerEvent<engine::ButtonComponent::Coords>("move button", [&](auto const& pos) {
				buttonComponent.node->setRelativePosition(pos);
				return 0;
			});

			scene.registerEvent<std::string>("set normal image", [&](auto const &image) {
				irr::video::ITexture *texture = game.textureManager.get(image);
				buttonComponent.node->setImage(texture);
				return 0;
			});
		});

		scene.registerEntityModel("image", [&](engine::Entity const& entity) {
			static irr::s32 id = 0;
			auto& imageComponent = entity.set<engine::ImageComponent>(game.device(),
										 game.textureManager.get("texture/placeholder1280x720.png"),
										 irr::core::position2d<irr::s32>(0,0),
										 true,
										 nullptr,
										 id,
										 nullptr);
		});
		scene.registerEvent<engine::GenericEvent>("create button", [&](engine::GenericEvent const&) {
			return scene.spawnEntity("button");
		});

		scene.spawnEntity("camera");
		engine::Menu::MyScriptParser parser("engine/menu/script/mainMenu", &scene, &game);

		parser.parseFile();
		parser.fillMap();

		game.eventsHandler.subscribe([&](engine::KeyState const& keystate) -> int {

			return 0;
		});
	};
}}
