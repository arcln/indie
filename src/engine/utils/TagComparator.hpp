/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include "engine/components/TagComponent.hpp"

namespace engine {

	/**
	 * Compare two Tags by their values
	 */
	class TagComparator {
	public:
		explicit TagComparator(std::string const& tag);

		bool operator()(TagComponent const& tagComponent) const;

	private:
		std::string _leftValue;
	};
}


