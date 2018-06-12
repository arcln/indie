/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** KeyFinder
*/

#pragma once

#include <irrlicht/Keycodes.h>
#include <iostream>
#include <unordered_map>
#include "../../../core/EventsHandler.hpp"

namespace engine { namespace Menu {

	class KeyFinder {
		public:
			KeyFinder();
			~KeyFinder() = default;

			std::string findKey(irr::EKEY_CODE key);

		protected:
			std::unordered_map<irr::EKEY_CODE, std::string, EnumClassHash> _keys;
	};
}}
