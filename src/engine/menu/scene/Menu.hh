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
#include <engine/components/DisplayComponent.hpp>
#include "engine/core/Scene.hpp"
#include "engine/core/Event.hpp"
#include "engine/core/Game.hpp"
#include "engine/components/CameraComponent.hpp"
#include "engine/components/ButtonComponent.hpp"
#include "engine/menu/classes/parsers/MyScriptParser.hpp"


namespace worms { namespace scene {

	static const auto menu = [](engine::Game& game, engine::Scene& scene) {
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

			scene.registerEvent<engine::ButtonComponent::Coords>("move button", [&](auto const& pos) {
				buttonComponent.node->setRelativePosition(pos);
				return 0;
			});

			scene.registerEvent<const wchar_t *>("set text", [&](auto const& text) {
				buttonComponent.node->setText(text);
				return 0;
			});

			scene.registerEvent<const wchar_t *>("set tooltip", [&](auto const& tooltip) {
				buttonComponent.node->setToolTipText(tooltip);
				return 0;
			});

			scene.registerEvent<irr::video::ITexture*>("set normal image", [&](auto const& image) {
				buttonComponent.node->setImage(image);
				return 0;
			});
		});

		scene.registerEvent<engine::GenericEvent>("create button", [&](engine::GenericEvent const&) {
			return scene.spawnEntity("button");
		});

		scene.spawnEntity("camera");
		engine::Menu::MyScriptParser parser("./script/postMenu", &scene, &game);
	};
}}
