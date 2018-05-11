/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <memory>
#include "Entity.hpp"

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

engine::Entity&
engine::Entity::copyComponents(engine::Entity const& entity)
{
	engine::ComponentPool::instance().copyComponents(_id, entity._id);
	return *this;
}

void engine::Entity::kill()
{
	auto entityIt = _entities->find(_parentId);

	for (; entityIt->first == _parentId ; entityIt++);

	if (_parentId != entityIt->first)
		throw std::runtime_error("unable to kill entity " + _id);

	engine::ComponentPool::instance().removeComponents(_id);
	_entities->erase(entityIt);
}

engine::EntityId
engine::Entity::getId() const
{
	return _id;
}
