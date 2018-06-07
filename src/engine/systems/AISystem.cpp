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
//		std::cout << "update" << std::endl;
		script.pCall(0, 0, 0);

		script.getGlobal("write_sum");
		script.pushInteger(12);
		script.pushInteger(3);
//		script.pushLightUserData(1);
		script.pCall(2, 1, 0);
//		script.pCall(2, 1, 0);

		int result = script.to<engine::Lua::Integer>(-1);
		std::cout << "cpp: " << result << std::endl;
		script.pop(1);
	});
}
