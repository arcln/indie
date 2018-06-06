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
	: _id(entity._id), _parentId(entity._parentId), _entities(entity._entities)
{
    std::cout << "cc" << std::endl;
}

engine::Entity&
engine::Entity::operator=(const engine::Entity& entity)
{
    _parentId = entity._parentId;
    _entities = entity._entities;
	_id = entity._id;
	return *this;
}

engine::Entity::~Entity()
{
}

void
engine::Entity::kill()
{
	_entities->remove(_id);
}

void
engine::Entity::attach(engine::Entity const& child) const
{
	_entities->attach(_id, child);
}

void
engine::Entity::detach()
{
	_entities->detach(*this);
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
