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

		scene.registerEvent<engine::GenericEvent>("loadMeshes", [&](engine::GenericEvent const&) {
			engine::ResourceManager<engine::MeshNode*>::instance().asyncLoad({"obj/worm.obj"}).wait();
			return 0;
		});

		scene.registerEvent<engine::GenericEvent>("loadTextures", [&](engine::GenericEvent const&) {
			engine::ResourceManager<engine::Texture*>::instance().syncLoad({"texture/worm.png"});
			return 0;
		});

		/********************************************************************\
		|*					  			START								*|
		\********************************************************************/

		scene.triggerEvent<engine::GenericEvent>("loadMeshes");
		scene.triggerEvent<engine::GenericEvent>("loadTextures");
		game.replaceScene("battle");
	};
}}
