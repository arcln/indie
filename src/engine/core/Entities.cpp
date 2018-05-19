/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "Entity.hpp"
#include "Entities.hpp"

void
engine::Entities::add(engine::Entity const& entity, engine::EntityModel const& model)
{
	EntityId parentId = entity.getParentId();

	model(entity);

	if (parentId == engine::Entity::nullId)
		_roots.emplace(parentId, entity);

	_childs[parentId].emplace_back(entity);
}

void
engine::Entities::add(engine::Entity const&& entity, engine::EntityModel const& model)
{
	EntityId parentId = entity.getParentId();

	model(entity);

	if (parentId == engine::Entity::nullId)
		_roots.emplace(parentId, entity);

	_childs[parentId].emplace_back(entity);
}

void engine::Entities::remove(engine::EntityId id)
{
	Entity& entity = _roots[id];
	auto entityIt = _childs.find(entity.getParentId());

	for (; entityIt->first == entity.getParentId(); entityIt++);

	if (entity.getParentId() != entityIt->first)
		throw std::runtime_error("unable to kill entity " + std::to_string(entity.getId()));

	_roots.erase(id);
	_childs.erase(entityIt);
}
