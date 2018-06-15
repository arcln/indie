/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <functional>
#include <map>
#include <vector>
#include <irrlicht/irrlicht.h>

namespace engine {

	using EntityModel = std::function<void (class Entity const&)>;

	class Entities {
	public:
		using Siblings = std::vector<EntityId>;
		using Container = std::unordered_map<EntityId, Siblings>;
		struct FindResult {
			Siblings& siblings;
			Siblings::iterator it;
		};

		Entity add(EntityId parentId, EntityModel const& model);
		void remove(EntityId parentId, EntityId id);

		FindResult find(EntityId parentId, EntityId id);
		EntityId findParent(EntityId id) const;

		Entity attach(EntityId parentId, EntityId id, EntityId newParentId);
		Entity detach(EntityId parentId, EntityId id);

		void enable(EntityId parentId, EntityId id);
		void disable(EntityId parentId, EntityId id);

		template <typename... ComponentsTypes>
		void each(typename EntityCallback<ComponentsTypes...>::Get const& callback, bool doChilds = true)
		{
			this->eachChilds<ComponentsTypes...>(Entity::nullId, callback, doChilds);
		}

		template <typename... ComponentsTypes>
		void eachChilds(EntityId parentId, typename EntityCallback<ComponentsTypes...>::Get const& callback, bool doChilds = true)
		{
			_eachSibilings<ComponentsTypes...>(parentId, _entities[parentId], callback, doChilds);
		}

		void withTag(std::string tag, std::function<void (Entity const&)> callback);

		Entity
		getParentEntity(Entity const& entity)
		{
			auto parentID = entity.getParentId();

			if (parentID == Entity::nullId) {
				throw std::runtime_error("unable to get parent entity of " + std::to_string(entity.getId()));
			}

			return Entity(parentID, this->findParent(parentID), this);
		}

	private:
		static EntityId _LastSpawnedEntityId;
		Container _entities;
		Container _disabledEntities;
		static const irr::core::vector3df _DisabledOffset;

		bool _remove(EntityId parentId, EntityId id, Container& container);
		void _removeChilds(EntityId id, Container& container);
		FindResult _find(EntityId parentId, EntityId id, Container& container);

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
					this->_eachSibilings<ComponentsTypes...>(it, childsIt->second, callback, doChilds);
			}
		}
	};
}
