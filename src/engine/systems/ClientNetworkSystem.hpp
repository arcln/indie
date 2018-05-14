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

	using Events = std::unordered_map<std::string, std::shared_ptr<Event<GenericEvent>>>;

	class ClientNetworkSystem : public System {
	public:
		explicit ClientNetworkSystem(network::ClientSocket& socket, Events const& events);
		~ClientNetworkSystem();

		void update(Entities const& entities) override;

	private:
		std::thread _netThread;
	};
}

