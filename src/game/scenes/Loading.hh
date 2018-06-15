//
//  Loading.hh
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#pragma once

#include <iostream>
#include "engine/core/Game.hpp"

namespace worms { namespace scene {

	static const auto loading = [](engine::Game& game, engine::Scene& scene) {


		/********************************************************************\
		|*				  		CLIENT ONLY EVENTS							*|
		\********************************************************************/

		scene.registerEvent<engine::GenericEvent>("loadMeshes", 0, [&](engine::GenericEvent const&) {
			engine::ResourceManager<engine::MeshNode*>::instance().asyncLoad({"obj/worm.obj",
																			  "obj/silinoid.ms3d",
																			  "obj/missile.obj"
																			 }).wait();
			return 0;
		});

		scene.registerEvent<engine::GenericEvent>("loadTextures", 0, [&](engine::GenericEvent const&) {
			engine::ResourceManager<engine::Texture*>::instance().syncLoad({"texture/worm.png",
																			"texture/explosion_particle.jpg",
																			"texture/silinoid.png",
																			"texture/missile.png"
																		   });
			return 0;
		});

		/********************************************************************\
		|*					  			START								*|
		\********************************************************************/

		scene.triggerEvent<engine::GenericEvent>("loadMeshes", 0);
		scene.triggerEvent<engine::GenericEvent>("loadTextures", 0);
		game.replaceScene("battle");
	};
}}
