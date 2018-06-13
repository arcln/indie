/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "TimeoutSystem.hpp"
#include "engine/components/TimeoutComponent.hpp"

void engine::TimeoutSystem::update(engine::Scene& scene, float tick)
{
	scene.getEntities().each<TimeoutComponent>([tick](Entity const& entity, auto& timeouts) {
		for (auto& timeout : timeouts) {
			if (timeout.remaining > 0) {
				timeout.remaining -= tick;
			} else if (!timeout.done) {
				timeout.callback();
				timeout.done = true;
			}
		}
	});
}
