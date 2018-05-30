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
		using Siblings = std::vector<Entity>;
		using Childs = std::map<EntityId, Siblings>;

		void add(Entity const& entity, EntityModel const& model);
		void add(Entity const&& entity, EntityModel const& model);
		void remove(EntityId id);

		void attach(EntityId parentId, Entity const& child);
		void detach(Entity const& entity);

		template <typename... ComponentsTypes>
		void each(typename EntityCallback<ComponentsTypes...>::Get const& callback, bool doChilds = true) const
		{
			for (auto& root : _roots) {
				try {
					_getEntityComponents<ComponentsTypes...>(root.second, callback);
					if (doChilds)
						this->eachChilds<ComponentsTypes...>(root.first, callback);
				} catch (internal::ComponentPoolException const& e) {}
			}
		}

		template <typename... ComponentsTypes>
		void eachChilds(EntityId parentId, typename EntityCallback<ComponentsTypes...>::Get const& callback) const
		{
			Childs::const_iterator childs = _childs.find(parentId);

			if (childs == std::end(_childs))
				return;

			for (auto& it : childs->second) {
				try {
					_getEntityComponents<ComponentsTypes...>(it, callback);
					this->eachChilds<ComponentsTypes...>(it.getId(), callback);
				} catch (internal::ComponentPoolException const& e) {}
			}
		}

		void withTag(std::string tag, std::function<void (Entity const&)> callback);

	private:
		Roots _roots;
		Childs _childs;

		template<typename... ComponentsTypes>
		void
		_getEntityComponents(Entity const& entity, typename EntityCallback<ComponentsTypes...>::Get const& callback) const
		{
			entity.get<ComponentsTypes...>([&](typename ComponentsTypes::Constraint::ReturnType... components) {
				callback(entity, components...);
			});
		}
	};
}
