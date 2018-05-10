/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <memory>
#include <map>
#include <typeindex>
#include <unordered_map>
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>
#include "engine/components/TestComponent.hpp"
#include "engine/components/DisplayComponent.hpp"
#include "engine/components/ComponentVisitor.hpp"

namespace engine {

	using AnyComponent = boost::variant<TestComponent, DisplayComponent>;

	using AnyComponents = std::unordered_map<std::type_index, std::multimap<EntityId, AnyComponent> >;

	template <typename ComponentType>
	using Components = std::multimap<EntityId, ComponentType>;

	using AnyEntityComponents = std::unordered_map<std::type_index, std::multimap<EntityId, AnyComponent> >;

	template <typename ComponentType>
	using UniqueComponents = std::map<EntityId, std::shared_ptr<ComponentType> >;

	/**
	 * Contains several type of components attached to Entities by EntityId
	 */
	class ComponentPool {
	public:

		template <typename ComponentType>
		ComponentType&
		addComponent(EntityId entityId)
		{
			Components<AnyComponent>& components = getComponents<ComponentType>();
			Components<AnyComponent>::iterator componentIt = components.emplace(entityId, ComponentType());

			if (componentIt == std::end(components))
				throw std::runtime_error("unable to add a new component");
			return boost::get<ComponentType>(componentIt->second);
		}

		template <typename ComponentType>
		ComponentType&
		getComponent(EntityId entityId)
		{
			Components<AnyComponent>& components = getComponents<ComponentType>();
			Components<AnyComponent>::iterator componentIt = components.find(entityId);

			if (componentIt == std::end(components))
				throw std::runtime_error("component not found");
			return boost::get<ComponentType>(componentIt->second);

		}

		template <typename ComponentType>
		typename Components<ComponentType>::iterator
		getComponents(EntityId entityId)
		{
			return getComponents<ComponentType>().find(entityId);
		}

		template <typename ComponentType>
		Components<AnyComponent>& getComponents()
		{
			return _components[typeid(ComponentType)];
		}

		void copyComponents(EntityId dest, EntityId src);

	private:
		AnyComponents _components;
	};
}


