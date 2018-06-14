/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Menu Hh
*/

#pragma once

#include <iostream>
#include <engine/components/LightComponent.hpp>
#include <engine/components/IrrlichtComponent.hpp>
#include "engine/core/Scene.hpp"
#include "engine/core/Event.hpp"
#include "engine/core/Game.hpp"
#include "engine/components/CameraComponent.hpp"
#include "engine/components/ButtonComponent.hpp"
#include "engine/components/ImageComponent.hpp"
#include "engine/components/TextComponent.hpp"
#include "engine/components/CheckBoxComponent.hpp"
#include "engine/components/EditBoxComponent.hpp"
#include "engine/menu/classes/parsers/MyScriptParser.hpp"
#include "game/events/Vector.hpp"

namespace worms { namespace scene {

	static const auto gameOver = [](engine::Game& game, engine::Scene& scene) {
		scene.registerEntityModel("camera", [&](engine::Entity const& entity) {
			auto& cameraComponent = entity.set<engine::CameraComponent>(game.device(),
										    engine::CameraComponent::Coords {
											    0.f, 0.f, -10.f},
										    engine::CameraComponent::Coords {0,
														     0,
														     0}
			);

			scene.registerEvent<engine::CameraComponent::Coords>("set camera position", 0, [&](auto const& position) {
				cameraComponent.node->setPosition(position);
				return 0;
			});

			scene.registerEvent<engine::CameraComponent::Coords>("set camera lookat", 0, [&](auto const& position) {
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

			scene.registerEvent<engine::ButtonComponent::Coords>("move button", 0, [&](auto const& pos) {
				buttonComponent.node->setRelativePosition(pos);
				return 0;
			});

			scene.registerEvent<std::string>("set normal image", 0, [&](auto const &image) {
				irr::video::ITexture *texture = engine::ResourceManager<engine::Texture*>::instance().get(image);
				buttonComponent.node->setImage(texture);
				return 0;
			});
		});

		scene.registerEntityModel("image", [&](engine::Entity const& entity) {
			static irr::s32 id = 0;
			auto& imageComponent = entity.set<engine::ImageComponent>(game.device(),
										 engine::ResourceManager<engine::Texture*>::instance().get("texture/placeholder1280x720.png"),
										 irr::core::position2d<irr::s32>(0,0),
										 true,
										 nullptr,
										 id,
										 nullptr);
			imageComponent.node->setUseAlphaChannel(true);
		});

		scene.registerEntityModel("staticText", [&](engine::Entity const& entity) {
			static irr::s32 id = 0;
			auto& staticTextComponent = entity.set<engine::TextComponent>(game.device(),
										      L"TEST TEXT",
										      irr::core::rect<irr::s32>(10, 10, 2000, 2000),
										      false,
										      false,
										      nullptr,
										      id,
										      false);
			staticTextComponent.node->setWordWrap(false);
		});

		scene.registerEntityModel("editBox", [&](engine::Entity const& entity) {
			static irr::s32 id = 0;
			auto& editBoxComponent = entity.set<engine::EditBoxComponent>(game.device(),
										      L"",
										      irr::core::rect<irr::s32>(10, 10, 200, 200),
										      false,
										      nullptr,
										      id);
			editBoxComponent.node->setDrawBackground(true);
		});

		scene.registerEntityModel("checkBox", [&](engine::Entity const& entity) {
			static irr::s32 id = 0;
			auto& checkBoxComponent = entity.set<engine::CheckBoxComponent>(game.device(),
											false,
											irr::core::rect<irr::s32>(10, 10, 200, 200),
											nullptr,
											id,
											nullptr);
			checkBoxComponent.node->setChecked(false);
		});

		scene.registerEvent<std::string>("set Winner", 0, [&](std::string const &name) {
			engine::Entities entities = scene.getEntities();

			entities.each<engine::TextComponent>([&](auto const& e, auto& text) {
				std::string nodeName = text.node->getName();
				if (nodeName == "Winner") {
					std::string nbStr = name;
					std::wstring str = std::wstring(nbStr.begin(), nbStr.end());
					const wchar_t *tmp = str.c_str();
					text.node->setText(tmp);
					(void) e;
				}
			});
			return 0;
		});

		scene.registerEvent<engine::GenericEvent>("Main Menu", 0, [&](engine::GenericEvent const&) {
			game.replaceScene("mainMenu");
			return 0;
		});

		scene.registerEvent<bool>("Quit", 0, [&](bool const&) {
			exit(0);
			return 0;
		});

		scene.spawnEntity("camera");
		engine::Menu::MyScriptParser parser("scripts/gameOver", &scene, &game);

		parser.parseFile();
		parser.fillMap();
	};
}}
