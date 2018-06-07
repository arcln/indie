/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include <algorithm>
#include <engine/components/IrrlichtComponent.hpp>
#include <engine/utils/TagComparator.hpp>
#include <engine/components/TransformComponent.hpp>
#include "engine/utils/EntityComparator.hpp"
#include "engine/components/TagComponent.hpp"
#include "engine/components/IrrlichtComponent.hpp"
#include "engine/core/Entity.hpp"
#include "engine/core/Entities.hpp"

engine::EntityId engine::Entities::_LastSpawnedEntityId = engine::Entity::nullId;
const irr::core::vector3df engine::Entities::_DisabledOffset(10000, 10000, 10000);

engine::Entity
engine::Entities::add(engine::EntityId parentId, engine::EntityModel const& model)
{
	Entity entity = Entity(++_LastSpawnedEntityId, parentId, this);

	model(entity);
	if (entity.has<IrrlichtComponent>())
		entity.get<TransformComponent>([](auto& t) {});

	_entities[parentId].push_back(entity.getId());
	return entity;
}

engine::Entities::FindResult
engine::Entities::find(engine::EntityId parentId, engine::EntityId id)
{
	return _find(parentId, id, _entities);
}

engine::EntityId
engine::Entities::findParent(engine::EntityId id) const
{
	for (auto& siblings : _entities) {
		auto const& entityIt = std::find(std::begin(siblings.second), std::end(siblings.second), id);

		if (entityIt != std::end(siblings.second))
			return siblings.first;
	}

	throw std::runtime_error("Unable to find a parent, entity not found.");
}

void
engine::Entities::remove(engine::EntityId parentId, engine::EntityId id)
{
	if (!_remove(parentId, id, _entities) && !_remove(parentId, id, _disabledEntities))
		throw std::runtime_error("Unable to remove an entity, Entity not found.");
}

engine::Entity
engine::Entities::attach(engine::EntityId parentId, engine::EntityId id, engine::EntityId newParentId)
{
	try {
		this->remove(parentId, id);
		_entities[newParentId].push_back(id);
	} catch (std::runtime_error const& e) {
		throw std::runtime_error(std::string("Unable to attach an entity: ") + e.what());
	}

	return engine::Entity(id, newParentId, this);
}

engine::Entity
engine::Entities::detach(engine::EntityId parentId, engine::EntityId id)
{
	if (parentId == engine::Entity::nullId)
		throw std::runtime_error("Unable to detach an entity without parent.");

	try {
		this->remove(parentId, id);
	} catch (std::runtime_error const& e) {
		throw std::runtime_error(std::string("Unable to detach an entity: ") + e.what());
	}

	_entities[engine::Entity::nullId].push_back(id);
	return engine::Entity(id, engine::Entity::nullId, this);
}

void
engine::Entities::withTag(std::string tag, std::function<void (engine::Entity const&)> callback)
{
	this->each<engine::TagComponent>([&tag, &callback](engine::Entity const& entity, auto const& tagComponents) {
		if (std::find_if(std::begin(tagComponents), std::end(tagComponents), engine::TagComparator(tag)) != std::end(tagComponents)) {
			callback(entity);
		}
	});
}

void
engine::Entities::enable(engine::EntityId parentId, engine::EntityId id)
{
	if (!_remove(parentId, id, _disabledEntities))
		return;

	_entities[parentId].push_back(id);

	if (IrrlichtComponent::Constraint::Pool::instance().has(id)) {
		IrrlichtComponent& irrlichtComponent = IrrlichtComponent::Constraint::Pool::instance().get(id);
		irrlichtComponent.node->setPosition(irrlichtComponent.node->getPosition() + engine::Entities::_DisabledOffset);
		irrlichtComponent.node->setScale(irrlichtComponent.node->getScale() / engine::Entities::_DisabledOffset);
	}
}

void
engine::Entities::disable(engine::EntityId parentId, engine::EntityId id)
{
	if (!_remove(parentId, id, _entities))
		return;

	_disabledEntities[parentId].push_back(id);

	if (IrrlichtComponent::Constraint::Pool::instance().has(id)) {
		IrrlichtComponent& irrlichtComponent = IrrlichtComponent::Constraint::Pool::instance().get(id);
		irrlichtComponent.node->setPosition(irrlichtComponent.node->getPosition() - engine::Entities::_DisabledOffset);
		irrlichtComponent.node->setScale(irrlichtComponent.node->getScale() * engine::Entities::_DisabledOffset);
	}
}

bool
engine::Entities::_remove(engine::EntityId parentId, engine::EntityId id, engine::Entities::Container& container)
{
	engine::Entities::FindResult findResult = _find(parentId, id, container);

	if (findResult.it == std::end(findResult.siblings))
		return false;

	findResult.siblings.erase(findResult.it);
	_removeChilds(id, container);
	return true;
}

void
engine::Entities::_removeChilds(engine::EntityId id, engine::Entities::Container& container)
{
	auto const& childs = container.find(id);

	if (childs != container.end()) {
		for (auto child : childs->second) {
			_removeChilds(child, container);
		}
		container.erase(childs);
	}
}

engine::Entities::FindResult
engine::Entities::_find(engine::EntityId parentId, engine::EntityId id, engine::Entities::Container& container)
{
	try {
		engine::Entities::Siblings& siblings = container[parentId];

		return FindResult {
			siblings,
			std::find(std::begin(siblings), std::end(siblings), id)
		};
	} catch (std::exception const& e) {
		throw std::runtime_error(std::string("Unable to find an entity: ") + e.what());
	}
}
