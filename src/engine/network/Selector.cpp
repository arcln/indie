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
	auto handler = [](ClientSocket client, DataHandlers dataHandlers) {
		try {
			std::cerr << "[server]: incoming connection" << std::endl;
			auto clientVersion = client.receive<TextMessage>();

			if (clientVersion.text == std::string(engine::network::version)) {
				client.send<TextMessage>(engine::network::version);
			} else {
				client.destroy();
				return;
			}

			std::cerr << "[server]: client connected" << std::endl;

			while (true) {
				auto msg = client.receive<TextMessage>();
				dataHandlers[typeid(TextMessage)](client, &msg);
			}
		} catch (std::exception& e) {
			std::cerr << "[server ERROR]: " << e.what() << std::endl;
			client.destroy();
			std::exit(1);
		}
	};

	std::thread master([&]() {
		std::cerr << "[server]: ready to accept incoming connections..." << std::endl;

		do {
			ClientSocket client;

			_serverSocket.accept(client.create());
			_clientSockets.push_back(client);
			_clients.emplace_back(std::thread(handler, client, _handlers));
			_clients.back().detach();
		} while (_clients.size() < NET_MAX_CONNECTIONS);

		_serverSocket.destroy();
	});

	return master;
}

std::vector<engine::network::ClientSocket> const&
engine::network::Selector::clients() const
{
	return _clientSockets;
}
