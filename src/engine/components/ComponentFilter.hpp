/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <functional>
#include "engine/core/EntityId.hpp"
#include "engine/components/ComponentPool.hpp"
#include "engine/components/UniqueComponentPool.hpp"

namespace engine {

	template<typename... ComponentsTypes>
	struct ComponentFilter {
		using Callback = std::function<void(typename ComponentsTypes::Constraint::Type&...)>;

		void get(EntityId entityId, Callback const& callback)
		{
			callback(ComponentsTypes::Constraint::Pool::instance().get(entityId)...);
		}
	};
}
