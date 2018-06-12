//
//  Engine.hpp
//  engine
//
//  Created by Arthur Chaloin on 30/05/2018.
//

#pragma once

#include <functional>
#include "engine/core/Game.hpp"

namespace engine {

	static const std::string DefaultAssetsRoot = "./assets/";
    static const std::size_t PhysicsCollideMaxObj = 3;

	class Engine {
	public:
		Engine(bool isServer, std::string const& cwd);

		int play(std::function<void (Game&)> const& gameModel);

	private:
		Game _game;
		bool _isServer;
	};
}
