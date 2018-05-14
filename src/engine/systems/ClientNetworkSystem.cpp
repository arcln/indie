//
//  ClientNetworkSystem.cpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#include <iostream>
#include "ClientNetworkSystem.hpp"

engine::ClientNetworkSystem::ClientNetworkSystem(engine::network::ClientSocket& socket, Events const&)
	: System(), _netThread([&]() {
		while (true) {
			auto msg = socket.receive<network::TextMessage>();
			std::cout << msg.text << std::endl;
		}
}) {}

engine::ClientNetworkSystem::~ClientNetworkSystem()
{
}

void
engine::ClientNetworkSystem::update(Entities const& entities)
{}
