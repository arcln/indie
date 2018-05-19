/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <functional>
#include <map>

namespace engine {

	using EntityModel = std::function<void (class Entity const&)>;

	class Entities {
	public:
		using Roots = std::map<EntityId, Entity>;
		using Childs = std::map<EntityId, std::vector<Entity> >;

		void add(Entity const& entity, EntityModel const& model);
		void add(Entity const&& entity, EntityModel const& model);
		void remove(EntityId id);

		template <typename... ComponentsTypes>
		void each(typename ComponentFilter<ComponentsTypes...>::Callback const& callback) const
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
		void _eachChilds(EntityId parentId, typename ComponentFilter<ComponentsTypes...>::Callback const& callback) const
		{
			Childs::const_iterator childs = _childs.find(parentId);

			if (childs == std::end(_childs))
				return;

			for (auto& it : childs->second) {
				try {
					it.get<ComponentsTypes...>(callback);
				} catch (internal::ComponentPoolException const& e) {
					continue;
				}
				_eachChilds<ComponentsTypes...>(it.getId(), callback);
			}
		}
	};
}
