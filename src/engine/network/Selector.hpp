//
//  Selector.hpp
//  engine
//
//  Created by Arthur Chaloin on 11/05/2018.
//

#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include "engine/network/Socket.hpp"
#include "engine/network/Socket.hpp"

namespace engine { namespace network {

	class Selector {
	public:
		using DataHandler = std::function<void (ClientSocket const&, void*)>;
		using DataHandlers = std::unordered_map<std::type_index, DataHandler>;

		template <typename DataType>
		void onData(DataHandler const& handler) {
			_handlers[typeid(DataType)] = handler;
		}

		std::thread run();
		std::vector<ClientSocket> const& clients() const;

	private:
		ServerSocket _serverSocket;
		std::thread _masterThread;
		std::mutex _clientsMutex;
		DataHandlers _handlers;
		std::vector<ClientSocket> _clientSockets;
		std::vector<std::thread> _clients;
	};
}}
