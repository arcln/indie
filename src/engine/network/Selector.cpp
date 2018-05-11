//
//  Selector.cpp
//  engine
//
//  Created by Arthur Chaloin on 11/05/2018.
//

#include <thread>
#include <iostream>
#include "Selector.hpp"
#include "Message.hpp"

std::thread
engine::network::Selector::run()
{
	auto handler = [](ClientSocket client, DataHandlersType dataHandlers) {
		try {
			auto clientVersion = client.receive<TextMessage>();

			if (clientVersion.text == std::string("v0.1")) {
				client.send<std::string>("OK");
			} else {
				client.send<std::string>("KO");
			}

			while (true) {
				auto msg = client.receive<TextMessage>();
				dataHandlers[typeid(TextMessage)](client, &msg);
			}
		} catch (std::exception& e) {
			std::cerr << "worms-server: " << e.what() << std::endl;
			client.destroy();
		}
	};

	std::thread master([&]() {
		do {
			ClientSocket client;

			_serverSocket.accept(client);
			_clients.emplace_back(std::thread(handler, std::move(client), _handlers));
		} while (_clients.size() < NET_MAX_CONNECTIONS);

		_serverSocket.destroy();
	});

	return master;
}
