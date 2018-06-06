//
//  ClientNetworkSystem.cpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#include <iostream>
#include "ClientNetworkSystem.hpp"

engine::ClientNetworkSystem::ClientNetworkSystem(engine::network::ClientSocket const& socket, Scene::Events& events)
	: System(), _netThread([socket](Scene::Events events) {
		while (true) {
			std::string msg = socket.receive<network::TextMessage>().text;
			std::string head = msg.substr(0, msg.find('|'));
			std::string body = msg.substr(msg.find('|') + 1);

			reinterpret_cast<Event<std::string>*>(events[head])->emit(body);
		}
}, events) {}

engine::ClientNetworkSystem::~ClientNetworkSystem()
{
	_netThread.detach();
}

void
engine::ClientNetworkSystem::update(Scene&)
{}
