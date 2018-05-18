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

	template<typename ComponentConstraint>
	struct SimpleFilter {
		typename ComponentConstraint::ReturnType get(EntityId entityId)
		{
			return ComponentConstraint::Pool::instance().get(entityId);
		}
	};

	template<typename... ComponentsTypes>
	class Filter;

	template<typename ComponentType>
	struct Filter<ComponentType> {
		using C1 = typename ComponentType::Constraint;
		using Callback = std::function<void(typename C1::Type&)>;

		void get(EntityId entityId, Callback const& callback)
		{
			callback(SimpleFilter<C1>().get(entityId));
		}
	};

	template<typename Component1Type, typename Component2Type>
	struct Filter<Component1Type, Component2Type> {
		using C1 = typename Component1Type::Constraint;
		using C2 = typename Component2Type::Constraint;
		using Callback = std::function<void(typename C1::Type&,
						    typename C2::Type&)>;

		void get(EntityId entityId, Callback const& callback)
		{
			callback(SimpleFilter<C1>().get(entityId),
				 SimpleFilter<C2>().get(entityId));
		}
	};
}
