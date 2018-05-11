/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "Entities.hpp"

void
engine::Entities::add(engine::Entity const& entity)
{
	EntityId parentId = entity.getParentId();

	_entities.emplace(parentId, entity);
	_childs.emplace(parentId, entity);
}

void
engine::Entities::add(engine::Entity const&& entity)
{
	EntityId parentId = entity.getParentId();

	_entities.emplace(parentId, entity);
	_childs.emplace(parentId, entity);
}
engine::Entity const&
engine::Entities::get(engine::EntityId id)
{
	return _entities[id];
}

void engine::Entities::remove(engine::EntityId id)
{
	Entity& entity = _entities[id];
	auto entityIt = _childs.find(entity.getParentId());

	for (; entityIt->first == entity.getParentId (); entityIt++);

	if (entity.getParentId() != entityIt->first)
		throw std::runtime_error("unable to kill entity " + entity.getId());

	_entities.erase(id);
	_childs.erase(entityIt);
}
