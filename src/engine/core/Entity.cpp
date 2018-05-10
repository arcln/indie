/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <memory>
#include "Entity.hpp"

engine::EntityId engine::Entity::_nextId = 0;

engine::Entity::Entity(ComponentPool& componentPool)
	: _id(Entity::_nextId), _componentPool(componentPool)
{
	++Entity::_nextId;
}

engine::Entity::~Entity()
{
}

engine::EntityId
engine::Entity::getId() const
{
	return _id;
}

engine::TestComponent&
engine::Entity::addTestComponent() const
{
	return _componentPool.addComponent<TestComponent>(_id);
}

engine::TestComponent&
engine::Entity::getTestComponent() const
{
	return _componentPool.getComponent<TestComponent>(_id);
}
