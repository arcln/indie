/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "ComponentPoolException.hpp"

engine::internal::ComponentPoolException::ComponentPoolException(std::string const& error) : runtime_error(error)
{}

engine::internal::ComponentPoolException::ComponentPoolException(std::runtime_error const& error) : runtime_error(error)
{}

engine::internal::ComponentPoolException::ComponentPoolException(char const* error) : runtime_error(error)
{}
