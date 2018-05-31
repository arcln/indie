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

	class Engine {
	public:
		Engine(bool isServer = false);

		int play(std::function<void (Game&)> const& gameModel);

	private:
		Game _game;
		bool _isServer;
	};
}
