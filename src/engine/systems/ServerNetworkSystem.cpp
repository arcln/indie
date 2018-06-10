//
//  ServerNetworkSystem.cpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#include "ServerNetworkSystem.hpp"

engine::ServerNetworkSystem::ServerNetworkSystem() : System()
{
	_selector.onData<network::TextMessage>([&](network::ClientSocket const& client, void* msg) {
		std::cerr << "worms-server: received event ["
				  << reinterpret_cast<network::TextMessage*>(msg)->text
				  << "] from client #"
				  << client.id
				  << std::endl;

		for (auto& c : _selector.clients()) {
			if (c.id != client.id) {
				c.send<network::TextMessage>(std::string(reinterpret_cast<network::TextMessage*>(msg)->text));
			}
		}
	});

	_selectorThread = _selector.run();
}

engine::ServerNetworkSystem::~ServerNetworkSystem()
{
	_selectorThread.join();
}

void
engine::ServerNetworkSystem::update(Scene&)
{}
