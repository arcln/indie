/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <engine/core/Entity.hpp>
#include <engine/components/IrrlichtComponent.hpp>

namespace engine {

	class EntityModelProvider {
	public:
		EntityModelProvider(Scene &scene) : _scene(scene) {}

		template <char ...NAME>
		EntityModel const& get()
		{
			throw std::runtime_error("aze");
//			throw ("Unable to find the EntityModel named " + NAME);
		}

	private:
		Scene &_scene;
	};
}

template <"animated">
engine::EntityModel const&
engine::EntityModelProvider::get()
{
	return nullptr;
}

//scene.registerEntityModel("animated", [&](engine::Entity const& entity) {
//	auto& irrlichtComponent = entity.set<engine::IrrlichtComponent>(&game, "obj/silinoid.ms3d");
//	irrlichtComponent.node->setPosition(irr::core::vector3df {1.f, -3.f, 0.f});
//	irrlichtComponent.node->setScale(irr::core::vector3df {.5f, .5f, .5f});
//	irrlichtComponent.node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//
//	auto& anim = entity.set<engine::AnimationComponent>("idle", 30);
//	anim.states["idle"] = engine::AnimationBoundaries(40, 118);
//	anim.states["run"] = engine::AnimationBoundaries(0, 39);
//
//	scene.registerEvent<bool>("anim1", [&anim](bool) {
//		anim.currentState = "run";
//		return 0;
//	});
//
//	scene.registerEvent<bool>("anim2", [&anim](bool) {
//		anim.currentState = "idle";
//		return 0;
//	});
//});