//
//  ServerNetworkSystem.hpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#pragma once

#include <thread>
#include "engine/core/System.hpp"
#include "engine/network/Selector.hpp"

namespace engine {

	class ServerNetworkSystem : public System {
	public:
		ServerNetworkSystem();
		~ServerNetworkSystem();

		void update(Scene& scene, float tick) override;

	private:
		network::Selector _selector;
		std::thread _selectorThread;
	};
}
