/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <stdexcept>

namespace engine { namespace internal {

		class ComponentPoolException : public std::runtime_error {
		public:
			explicit ComponentPoolException(std::string const& error);

			explicit ComponentPoolException(runtime_error const& error);

			explicit ComponentPoolException(char const* error);
		};
	};
};
