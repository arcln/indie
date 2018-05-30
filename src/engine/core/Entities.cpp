/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include <algorithm>
#include "engine/utils/EntityComparator.hpp"
#include "engine/core/Entity.hpp"
#include "engine/core/Entities.hpp"

void
engine::Entities::add(engine::Entity const& entity, engine::EntityModel const& model)
{
	EntityId parentId = entity.getParentId();

	model(entity);

	if (parentId == engine::Entity::nullId)
		_roots.emplace(entity.getId(), entity);

	_childs[parentId].emplace_back(entity);
}

void
engine::Entities::add(engine::Entity const&& entity, engine::EntityModel const& model)
{
	EntityId parentId = entity.getParentId();

	model(entity);

	if (parentId == engine::Entity::nullId)
		_roots.emplace(entity.getId(), entity);

	_childs[parentId].emplace_back(entity);
}

void
engine::Entities::remove(engine::EntityId id)
{
	Entity& entity = _roots[id];
	auto entityIt = _childs.find(entity.getParentId());

	for (; entityIt->first == entity.getParentId(); entityIt++);

	if (entity.getParentId() != entityIt->first)
		throw std::runtime_error("unable to kill entity " + std::to_string(entity.getId()));

	_roots.erase(id);
	_childs.erase(entityIt);
}

void
engine::Entities::attach(engine::EntityId parentId, engine::Entity const& child)
{
	auto const& childIt = _roots.find(child.getId());

	if (childIt != std::end(_roots))
		this->detach(child);

	_childs[parentId].emplace_back(childIt->second);
	_roots.erase(childIt);
}

void
engine::Entities::detach(engine::Entity const& entity)
{
	engine::EntityId parentId = entity.getParentId();
	engine::Entities::Siblings& siblings = _childs[parentId];

	if (parentId == engine::Entity::nullId)
		throw std::runtime_error("unable to detach an entity without parent");

	auto const& entityIt = std::find_if(std::begin(siblings), std::end(siblings), engine::EntityComparator(entity));

	if (entityIt != std::end(siblings)) {
		_roots[entity.getId()] = *entityIt;
		siblings.erase(entityIt);
	}
}
