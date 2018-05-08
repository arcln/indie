/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include "Entity.hpp"

engine::Entity::Entity() : _id(Entity::_nextId)
{
	++Entity::_nextId;
}

engine::Entity::~Entity()
{
}

void engine::Entity::addComponent(engine::Component& component) const
{
	// TODO send event to the scene
}

size_t engine::Entity::get_id() const
{
	return _id;
}
