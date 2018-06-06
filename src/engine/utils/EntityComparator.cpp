/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "EntityComparator.hpp"

engine::EntityComparator::EntityComparator(engine::Entity const& entity) : _leftId(entity.getId())
{}

bool
engine::EntityComparator::operator()(engine::Entity const& entity) const
{
	return _leftId == entity.getId();
}
