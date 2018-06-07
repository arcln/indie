/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <memory>
#include "Entity.hpp"
#include "Entities.hpp"

engine::EntityId const engine::Entity::nullId = 0;

engine::Entity::Entity()
{}

engine::Entity::Entity(EntityId id, EntityId parentId, Entities* entities)
	: _id(id), _parentId(parentId), _entities(entities)
{}

engine::Entity::Entity(engine::Entity const& entity)
	: _id(entity._id)
{}

engine::Entity&
engine::Entity::operator=(const engine::Entity& entity)
{
	_id = entity._id;
	return *this;
}

engine::Entity::~Entity()
{
}

void
engine::Entity::kill()
{
	_entities->remove(_parentId, _id);
}

engine::Entity
engine::Entity::attach(engine::Entity const& child) const
{
	return _entities->attach(_id, child.getId());
}

void
engine::Entity::detach()
{
	_entities->detach(_parentId, _id);
}

engine::EntityId
engine::Entity::getId() const
{
	return _id;
}

engine::EntityId
engine::Entity::getParentId() const
{
	return _parentId;
}
