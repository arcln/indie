/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include <algorithm>
#include <engine/components/TransformComponent.hpp>
#include <engine/utils/TagComparator.hpp>
#include "engine/utils/EntityComparator.hpp"
#include "engine/components/TagComponent.hpp"
#include "engine/components/IrrlichtComponent.hpp"
#include "engine/core/Entity.hpp"
#include "engine/core/Entities.hpp"

engine::EntityId engine::Entities::_LastSpawnedEntityId = engine::Entity::nullId;

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
	engine::Entities::Siblings& siblings = _entities.at(parentId);

	return FindResult {
		siblings,
		std::find(std::begin(siblings), std::end(siblings), id)
	};
}

engine::EntityId
engine::Entities::findParent(engine::EntityId id)
{
	for (auto& siblings : _entities) {
		auto const& entityIt = std::find(std::begin(siblings.second), std::end(siblings.second), id);

		if (entityIt != std::end(siblings.second))
			return siblings.first;
	}

	throw std::runtime_error("unable to find a parent, entity not found");
}

void
engine::Entities::remove(engine::EntityId parentId, engine::EntityId id)
{
	engine::Entities::FindResult findResult = this->find(parentId, id);

	if (findResult.it == std::end(findResult.siblings))
		throw std::runtime_error("unable to kill entity " + std::to_string(id));
	findResult.siblings.erase(findResult.it);
}

engine::Entity
engine::Entities::attach(engine::EntityId parentId, engine::EntityId id, engine::EntityId newParentId)
{
	try {
		this->remove(parentId, id);
	} catch (std::runtime_error const& e) {
		throw std::runtime_error(std::string("unable to attach an entity: ") + e.what());
	}

	_entities.at(newParentId).push_back(id);
	return engine::Entity(id, newParentId, this);
}

engine::Entity
engine::Entities::detach(engine::EntityId parentId, engine::EntityId id)
{
	if (parentId == engine::Entity::nullId)
		throw std::runtime_error("unable to detach an entity without parent");

	try {
		this->remove(parentId, id);
	} catch (std::runtime_error const& e) {
		throw std::runtime_error(std::string("unable to detach an entity: ") + e.what());
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
