/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <memory>
#include "Entity.hpp"

engine::Entity::Entity() : _componentPool(nullptr)
{}

engine::Entity::Entity(EntityId entityId, Entities* entities, ComponentPool* componentPool)
	: _id(entityId), _entities(entities), _componentPool(componentPool)
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

void engine::Entity::kill()
{
	auto const& entityIt = std::find(std::begin(*_entities), std::end(*_entities), _id);

	if (entityIt != std::end(*_entities)) {
		_componentPool->removeComponents(_id);
		_entities->erase(entityIt);
	}
}
