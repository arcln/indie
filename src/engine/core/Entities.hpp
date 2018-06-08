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
		using Siblings = std::vector<EntityId>;
		struct FindResult {
			Siblings& siblings;
			Siblings::iterator it;
		};

		Entity add(EntityId parentId, EntityModel const& model);
		void remove(EntityId parentId, EntityId id);

		FindResult find(EntityId parentId, EntityId id);
		EntityId findParent(EntityId id);

		Entity attach(EntityId parentId, EntityId id, engine::EntityId newParentId);
		Entity detach(EntityId parentId, EntityId id);

		template <typename... ComponentsTypes>
		void each(typename EntityCallback<ComponentsTypes...>::Get const& callback, bool doChilds = true)
		{
			this->_eachSibilings<ComponentsTypes...>(Entity::nullId, _entities[Entity::nullId], callback, doChilds);
		}

		void withTag(std::string tag, std::function<void (Entity const&)> callback);

	private:
		static EntityId _LastSpawnedEntityId;
		std::unordered_map<EntityId, Siblings> _entities;

		template<typename... ComponentsTypes>
		void
		_getEntityComponents(EntityId parentId, EntityId id, typename EntityCallback<ComponentsTypes...>::Get const& callback)
		{
			ComponentFilter<ComponentsTypes...>().get(id, [&](typename ComponentsTypes::Constraint::ReturnType&... components) {
				callback(Entity(id, parentId, this), components...);
			});
		}

		template <typename... ComponentsTypes>
		void _eachSibilings(EntityId parentId, Siblings& siblings, typename EntityCallback<ComponentsTypes...>::Get const& callback, bool doChilds)
		{
			for (auto& it : siblings) {
				try {
					_getEntityComponents<ComponentsTypes...>(parentId, it, callback);
				} catch (internal::ComponentPoolException const& e) {}

				auto const& childsIt = _entities.find(it);
				if (doChilds && childsIt != std::end(_entities))
					this->_eachSibilings<ComponentsTypes...>(parentId, childsIt->second, callback, doChilds);
			}
		}
	};
}
