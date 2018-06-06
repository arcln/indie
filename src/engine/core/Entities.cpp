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

	if (parentId == engine::Entity::nullId)
		_roots.push_back(entity.getId());

	_childs[parentId].push_back(entity.getId());
	return entity;
}

engine::Entities::Roots::iterator
engine::Entities::findRoot(engine::EntityId id)
{
	return std::find(std::begin(_roots), std::end(_roots), id);
}

engine::Entities::FindResult
engine::Entities::find(engine::EntityId parentId, engine::EntityId id)
{
	if (std::find(std::begin(_roots), std::end(_roots), parentId) == std::end(_roots))
		throw std::runtime_error("unable to find an entity, parent not found");

	engine::Entities::Siblings& siblings = _childs[parentId];

	return FindResult {
		siblings,
		std::find(std::begin(siblings), std::end(siblings), id)
	};
}

void
engine::Entities::remove(engine::EntityId parentId, engine::EntityId id)
{
	if (parentId == engine::Entity::nullId) {
		auto entityIt = this->findRoot(id);

		if (entityIt == std::end(_roots))
			throw std::runtime_error("unable to kill root entity " + std::to_string(id));
		_roots.erase(entityIt);
	} else {
		engine::Entities::FindResult findResult = this->find(parentId, id);

		if (findResult.it == std::end(findResult.siblings))
			throw std::runtime_error("unable to kill entity " + std::to_string(id));
		findResult.siblings.erase(findResult.it);
	}
}

engine::Entity
engine::Entities::attach(engine::EntityId parentId, engine::EntityId id)
{
	if (std::find(std::begin(_roots), std::end(_roots), parentId) == std::end(_roots))
		throw std::runtime_error("unable to attach an entity, parent not found");

	auto const& childIt = std::find(std::begin(_roots), std::end(_roots), id);

	if (childIt == std::end(_roots))
		this->detach(parentId, id);

	engine::Entities::FindResult findResult = this->find(parentId, id);
	findResult.siblings.erase(findResult.it);

	_childs[parentId].push_back(id);
	return engine::Entity(id, parentId, this);
}

engine::Entity
engine::Entities::detach(engine::EntityId parentId, engine::EntityId id)
{
	if (parentId == engine::Entity::nullId)
		throw std::runtime_error("unable to detach an entity without parent");

	try {
		engine::Entities::FindResult findResult = this->find(parentId, id);
		if (findResult.it == std::end(findResult.siblings))
			throw std::runtime_error("unable to detach an entity, entity not found");

		findResult.siblings.erase(findResult.it);
	} catch (std::runtime_error const& e) {
		throw std::runtime_error(std::string("unable to detach an entity, parent not found: ") + e.what());
	}

	_roots.push_back(id);
	return engine::Entity(id, parentId, this);
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
