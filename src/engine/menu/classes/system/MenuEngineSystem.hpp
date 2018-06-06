/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Menu Engine System Hpp
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "engine/core/Game.hpp"
#include "engine/resource/ResourceManager.hpp"
#include "engine/systems/System.hpp"

namespace engine { namespace Menu {

	class MenuEngineSystem : public engine::System {
		public:
			MenuEngineSystem();
			~MenuEngineSystem();

			void update(Entities const& entities) override;

		protected:
	};
}}

