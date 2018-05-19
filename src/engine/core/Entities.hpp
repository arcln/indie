/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <functional>

namespace engine {

	using EntityModel = std::function<void (class Entity const&)>;

	class Entities {
	public:
		using Roots = std::map<EntityId, Entity>;
		using Childs = std::multimap<EntityId, Entity>;

		void add(Entity const& entity, EntityModel const& model);
		void add(Entity const&& entity, EntityModel const& model);
		void remove(EntityId id);

		template <typename... ComponentsTypes>
		using EachCallback = std::function<void(typename ComponentsTypes::Constraint::Type&...)>;

		template <typename... ComponentsTypes>
		void each(EachCallback<ComponentsTypes...> const& callback) const
		{
			for (auto& root : _roots) {
				try {
					root.second.get<ComponentsTypes...>(callback);
				} catch (internal::ComponentPoolException const& e) {
					continue;
				}
				_eachChilds<ComponentsTypes...>(root.first, callback);
			}
		}
	private:
		Roots _roots;
		Childs _childs;

		template <typename... ComponentsTypes>
		void _eachChilds(EntityId parentId, std::function<void (typename ComponentsTypes::Constraint::Type&...)> const& callback) const
		{
			for (auto child = _childs.find(parentId); child->first == parentId; child++) {
				try {
					child->second.get<ComponentsTypes...>(callback);
				} catch (internal::ComponentPoolException const& e) {
					continue;
				}
				_eachChilds<ComponentsTypes...>(child->first, callback);
			}
		}
	};
}
