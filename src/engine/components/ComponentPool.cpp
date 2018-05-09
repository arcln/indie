/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include <memory>
#include "ComponentPool.hpp"

std::shared_ptr<engine::TestComponent>
engine::ComponentPool::addTestComponent(engine::EntityId entityId)
{
	engine::Components<engine::TestComponent>::iterator componentIt = _testComponents.emplace(entityId, std::make_shared<TestComponent>());

	return _addComponent<engine::TestComponent>(_testComponents, entityId);
}

std::shared_ptr<engine::TestComponent>
engine::ComponentPool::getTestComponent(EntityId entityId)
{
	return _getComponent<TestComponent>(_testComponents, entityId);
}
