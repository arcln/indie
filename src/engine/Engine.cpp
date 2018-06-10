//
//  Engine.cpp
//  engine
//
//  Created by Arthur Chaloin on 30/05/2018.
//

#include "Engine.hpp"
#include "engine/systems/ServerNetworkSystem.hpp"

engine::Engine::Engine(bool isServer, std::string const& cwd)
	: _game(!isServer, cwd.length() ? cwd + "/Contents/Resources/assets/" : DefaultAssetsRoot)
	, _isServer(isServer)
{}

int
engine::Engine::play(std::function<void (Game&)> const& model)
{
//	try {
		model(_game);

		if (_isServer) {
			_game.registerSystem("network", new ServerNetworkSystem());
		}

		_game.play("main");
//	} catch (std::exception& e) {
//		std::cerr << "worms: ERROR: " << e.what() << std::endl;
//		return 1;
//	}

	return 0;
}
