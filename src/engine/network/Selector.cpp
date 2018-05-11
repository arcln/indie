//
//  Selector.cpp
//  engine
//
//  Created by Arthur Chaloin on 11/05/2018.
//

#include <thread>
#include "Selector.hpp"
#include "Message.hpp"

void
engine::network::Selector::run()
{
	auto clientHandler = [](ClientSocket* client) {};

	std::thread master([&]() {
		do {
			auto t = std::thread(clientHandler, _clients.back().first);

			_clients.emplace_back(ClientSocket(), t);
			_serverSocket.accept(_clients.back().first);
			_clients.back().second.detach();
		} while (_clients.size() < NET_MAX_CONNECTIONS);
	});

	master.detach();
}
