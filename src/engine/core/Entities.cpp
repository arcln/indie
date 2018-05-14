/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "Entity.hpp"
#include "Entities.hpp"

void
engine::Entities::add(engine::Entity const& entity)
{
	EntityId parentId = entity.getParentId();

	_roots.emplace(parentId, entity);
	_childs.emplace(parentId, entity);
}

void
engine::Entities::add(engine::Entity const&& entity)
{
	EntityId parentId = entity.getParentId();

	if (parentId == engine::Entity::nullId)
		_roots.emplace(entity.getId(), entity);

	_childs.emplace(parentId, entity);
}

engine::Entities::Roots const&
engine::Entities::getRoots() const
{
	return _roots;
}

engine::Entities::Childs::iterator
engine::Entities::getChilds(EntityId id)
{
	return _childs.find(id);
}

void engine::Entities::remove(engine::EntityId id)
{
	Entity& entity = _roots[id];
	auto entityIt = _childs.find(entity.getParentId());

	for (; entityIt->first == entity.getParentId (); entityIt++);

	if (entity.getParentId() != entityIt->first)
		throw std::runtime_error("unable to kill entity " + std::to_string(entity.getId()));

	_roots.erase(id);
	_childs.erase(entityIt);
}
