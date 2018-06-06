/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "TagComparator.hpp"

engine::TagComparator::TagComparator(std::string const& tag) : _leftValue(tag)
{}

bool
engine::TagComparator::operator()(engine::TagComponent const& tagComponent) const
{
	return _leftValue == tagComponent.value;
}
