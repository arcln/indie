/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <thread>
#include <engine/utils/Lua.hpp>
#include <engine/resource/ResourceManager.hpp>
#include "engine/systems/System.hpp"

namespace engine {

	class AISystem : public System {
	public:
		AISystem(ResourceManager<Lua>& luaManager);

		void update(Scene& scene) override;

	private:
		ResourceManager<Lua>& _luaManager;
	};
}
