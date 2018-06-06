//
//  ClientNetworkSystem.hpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#pragma once

#include <thread>
#include "engine/core/Scene.hpp"
#include "engine/systems/System.hpp"
#include "engine/network/Selector.hpp"

namespace engine {

	class ClientNetworkSystem : public System {
	public:
		explicit ClientNetworkSystem(network::ClientSocket const& socket, Scene::Events& events);
		~ClientNetworkSystem();

		void update(Scene& scene) override;

	private:
		std::thread _netThread;
	};
}

