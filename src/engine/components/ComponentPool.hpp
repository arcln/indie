/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <memory>
#include <map>
#include "TestComponent.hpp"

namespace engine {

	template <typename ComponentType>
	using Components = std::multimap<EntityId, std::shared_ptr<ComponentType> >;

	template <typename ComponentType>
	using UniqueComponents = std::map<EntityId, std::shared_ptr<ComponentType> >;

	class ComponentPool {
	public:
		std::shared_ptr<TestComponent> addTestComponent(EntityId entityId);
		std::shared_ptr<TestComponent> getTestComponent(EntityId entityId);

	private:
		Components<TestComponent> _testComponents;

		template <typename ComponentType>
		std::shared_ptr<ComponentType>
		_addComponent(engine::Components<ComponentType> components, engine::EntityId entityId)
		{
			typename Components<ComponentType>::iterator componentIt = components.emplace(entityId, std::make_shared<ComponentType>());

			if (componentIt == std::end(components))
				throw std::runtime_error("unable to add a new component");
			return componentIt->second;
		}

		template <typename ComponentType>
		std::shared_ptr<ComponentType>
		_getComponent(engine::Components<ComponentType> components, engine::EntityId entityId)
		{
			typename Components<ComponentType>::iterator componentIt = components.find(entityId);

			if (componentIt == std::end(components))
				throw std::runtime_error("component not found");
			return componentIt->second;
		}

		template <typename ComponentType>
		typename Components<ComponentType>::iterator
		_getComponents(engine::Components<ComponentType> components, engine::EntityId entityId)
		{
			typename Components<ComponentType>::iterator componentsIt = components.find(entityId);

			if (componentsIt == std::end(components))
				throw std::runtime_error("components not found");
			return componentsIt;
		}
	};
}


