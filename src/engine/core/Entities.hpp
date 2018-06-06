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
		using Roots = std::vector<EntityId>;
		using Siblings = std::vector<EntityId>;
		using Childs = std::map<EntityId, Siblings>;
		struct FindResult {
			Siblings& siblings;
			Siblings::iterator it;
		};

		Entity add(EntityId parentId, EntityModel const& model);
		Roots::iterator findRoot(EntityId id);
		FindResult find(EntityId parentId, EntityId id);
		void remove(EntityId parentId, EntityId id);

		Entity attach(EntityId parentId, EntityId id);
		Entity detach(EntityId parentId, EntityId id);

		template <typename... ComponentsTypes>
		void each(typename EntityCallback<ComponentsTypes...>::Get const& callback, bool doChilds = true)
		{
			for (auto& child : _childs) {
				try {
					_getEntityComponents<ComponentsTypes...>(Entity::nullId, child.first, callback);
				} catch (internal::ComponentPoolException const& e) {}

				if (doChilds)
					this->_eachSibilings<ComponentsTypes...>(child.first, child.second, callback);
			}
		}

		void withTag(std::string tag, std::function<void (Entity const&)> callback);

	private:
		static EntityId _LastSpawnedEntityId;
		Roots _roots;
		Childs _childs;

		template<typename... ComponentsTypes>
		void
		_getEntityComponents(EntityId parentId, EntityId id, typename EntityCallback<ComponentsTypes...>::Get const& callback)
		{
			ComponentFilter<ComponentsTypes...>().get(id, [&](typename ComponentsTypes::Constraint::ReturnType&... components) {
				callback(Entity(id, parentId, this), components...);
			});
		}

		template <typename... ComponentsTypes>
		void _eachSibilings(EntityId parentId, Siblings& siblings, typename EntityCallback<ComponentsTypes...>::Get const& callback)
		{
			for (auto& it : siblings) {
				try {
					_getEntityComponents<ComponentsTypes...>(parentId, it, callback);
				} catch (internal::ComponentPoolException const& e) {}

				auto const& childsIt = _childs.find(it);
				if (childsIt != std::end(_childs))
					this->_eachSibilings<ComponentsTypes...>(parentId, childsIt->second, callback);
			}
		}
	};
}
