//
//  ServerNetworkSystem.cpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#include "ServerNetworkSystem.hpp"

engine::ServerNetworkSystem::ServerNetworkSystem() : System()
{
	_selector.onData<network::TextMessage>([](network::ClientSocket const& client, void* msg) {
		std::cout << reinterpret_cast<network::TextMessage*>(msg)->text << std::endl;
	});

	_selectorThread = _selector.run();
}

engine::ServerNetworkSystem::~ServerNetworkSystem()
{
	_selectorThread.join();
}

void
engine::ServerNetworkSystem::update(Entities const&)
{}
