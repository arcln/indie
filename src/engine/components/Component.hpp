/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <cstddef>

namespace engine {

	enum class ComponentType {
		TEST_COMPONENT
	};

	struct ComponentTypeHash
	{
		template <typename T>
		std::size_t operator()(T t) const
		{
			return static_cast<std::size_t>(t);
		}
	};

	struct Component {
	};

	struct UniqueComponent : Component {
	};
}
