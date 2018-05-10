/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <boost/variant/static_visitor.hpp>

namespace engine {

	template <typename ComponentType>
	class ComponentVisitor : public boost::static_visitor<ComponentType> {
	public:
		ComponentType& operator()(ComponentType& component)
		{
			return component;
		}
	};
}
