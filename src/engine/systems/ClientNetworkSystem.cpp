//
//  ClientNetworkSystem.cpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#include <iostream>
#include "ClientNetworkSystem.hpp"

engine::ClientNetworkSystem::ClientNetworkSystem(engine::network::ClientSocket const& socket, Events const&)
	: System(), _netThread([socket]() {
		while (true) {
			auto msg = socket.receive<network::TextMessage>();
			std::cout << msg.text << std::endl;
		}
}) {}

engine::ClientNetworkSystem::~ClientNetworkSystem()
{
	_netThread.detach();
}

void
engine::ClientNetworkSystem::update(Entities const& entities)
{}
