/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <memory>
#include "Entity.hpp"

engine::EntityId engine::Entity::_nextId = -1;

engine::Entity::Entity() : _componentPool((engine::ComponentPool*)42)
{}

engine::Entity::Entity(ComponentPool* componentPool)
	: _id(++Entity::_nextId), _componentPool(componentPool)
{}

engine::Entity::Entity(engine::Entity const& entity)
	: _id(entity._id), _componentPool(entity._componentPool)
{}

engine::Entity&
engine::Entity::operator=(const engine::Entity& entity)
{
	_id = entity._id;
	_componentPool = entity._componentPool;
	return *this;
}

engine::Entity::~Entity()
{
}

engine::Entity&
engine::Entity::copyComponents(engine::Entity const& entity)
{
	_componentPool->copyComponents(_id, entity._id);
	return *this;
}

engine::EntityId
engine::Entity::getId() const
{
	return _id;
}
