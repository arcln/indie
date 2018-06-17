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
#include "engine/menu/classes/parsers/MyScriptParser.hpp"
#include "engine/menu/classes/utils/KeyFinder.hpp"
#include "game/events/Vector.hpp"

namespace worms { namespace scene {

	static const auto keyAssign = [](engine::Game& game, engine::Scene& scene) {
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
										      irr::core::rect<irr::s32>(10, 10, 200, 200),
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

		scene.registerEvent<engine::GenericEvent>("key left", 0, [&](engine::GenericEvent const&) {
			engine::Entities entities = scene.getEntities();
			static int check = 0;

			if (check == 0) {
				entities.each<engine::ButtonComponent>([&](auto const& e, auto& button) {
					std::string name = button.node->getName();
					if (name != "key left") {
						button.node->setPressed(false);
					}
					(void) e;
				});
			}
			check = (check + 1) % 10;
			return 0;
		});

		scene.registerEvent<engine::GenericEvent>("key right", 0, [&](engine::GenericEvent const&) {
			engine::Entities entities = scene.getEntities();
			static int check = 0;

			if (check == 0) {
				entities.each<engine::ButtonComponent>([&](auto const& e, auto& button) {
					std::string name = button.node->getName();
					if (name != "key right") {
						button.node->setPressed(false);
					}
					(void) e;
				});
			}
			check = (check + 1) % 10;
			return 0;
		});

		scene.registerEvent<engine::GenericEvent>("jump", 0, [&](engine::GenericEvent const&) {
			engine::Entities entities = scene.getEntities();
			static int check = 0;

			if (check == 0) {
				entities.each<engine::ButtonComponent>([&](auto const& e, auto& button) {
					std::string name = button.node->getName();
					if (name != "jump") {
						button.node->setPressed(false);
					}
					(void) e;
				});
			}
			check = (check + 1) % 10;
			return 0;
		});

		scene.registerEvent<engine::GenericEvent>("shoot", 0, [&](engine::GenericEvent const&) {
			engine::Entities entities = scene.getEntities();
			static int check = 0;

			if (check == 0) {
				entities.each<engine::ButtonComponent>([&](auto const& e, auto& button) {
					std::string name = button.node->getName();
					if (name != "shoot") {
						button.node->setPressed(false);
					}
					(void) e;
				});
			}
			check = (check + 1) % 10;
			return 0;
		});

		scene.registerEvent<engine::GenericEvent>("validate", 0, [&](engine::GenericEvent const&) {
			engine::Entities entities = scene.getEntities();
			static int check = 0;

			if (check == 0) {
				entities.each<engine::ButtonComponent>([&](auto const& e, auto& button) {
					std::string name = button.node->getName();
					if (name != "validate") {
						button.node->setPressed(false);
					}
					(void) e;
				});
			}
			check = (check + 1) % 10;
			return 0;
		});

		scene.registerEvent<engine::GenericEvent>("grab", 0, [&](engine::GenericEvent const&) {
			engine::Entities entities = scene.getEntities();
			static int check = 0;

			if (check == 0) {
				entities.each<engine::ButtonComponent>([&](auto const& e, auto& button) {
					std::string name = button.node->getName();
					if (name != "grab") {
						button.node->setPressed(false);
					}
					(void) e;
				});
			}
			check = (check + 1) % 10;
			return 0;
		});

		scene.registerEvent<Vector2i>("assign key", 0, [&](Vector2i const& key) {
			engine::Entities entities = scene.getEntities();
			entities.each<engine::ButtonComponent>([&](auto const& e, auto& button) {
				std::string name = button.node->getName();
				if (button.node->isPressed() == true) {
					engine::Menu::KeyFinder finder;
					std::string str = finder.findKey((irr::EKEY_CODE)key.x);
					std::wstring widestr = std::wstring(str.begin(), str.end());
					const wchar_t *tmp = widestr.c_str();

					button.node->setText(tmp);
					button.node->setPressed(false);
				}
				(void) e;
			});

			return 0;
		});

		scene.registerEvent<engine::GenericEvent>("create button", 0, [&](engine::GenericEvent const&) {
			scene.spawnEntity("button");
			return 0;
		});

		scene.registerEvent<Vector2i>("go back", 0, [&](Vector2i const&) {
			game.replaceScene("optionsMenu");
			return 0;
		});

		scene.spawnEntity("camera");
		engine::Menu::MyScriptParser parser("scripts/keyAssignement", &scene, &game);

		parser.parseFile();
		parser.fillMap();

		//game.eventsHandler.subscribe<Vector2i>(scene, irr::KEY_KEY_O, "O", Vector2i(0, 0), 0);
		for (int i = 0; i < 166; i = i + 1) {
			game.eventsHandler.subscribe<Vector2i>(scene, (irr::EKEY_CODE)i, "assign key", 0, Vector2i(i, 0), 0);
		}
	};
}}
