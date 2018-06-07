/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include <engine/components/AIComponent.hpp>
#include "AISystem.hpp"
#include "engine/core/Entities.hpp"

engine::AISystem::AISystem(engine::ResourceManager<engine::Lua>& luaManager) : _luaManager(luaManager)
{

}

void
engine::AISystem::update(Scene& scene)
{
	scene.getEntities().each<AIComponent>([&](auto const& e, auto& ai) {
		Lua const& script = _luaManager.get(ai.scriptPath);
		script.getGlobal("update");
		script.pCall(0, 0, 0);
	});
}
