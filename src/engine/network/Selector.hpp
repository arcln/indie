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
		using DataHandlerType = std::function<void (ClientSocket const&, void*)>;
		using DataHandlersType = std::unordered_map<std::type_index, DataHandlerType>;

		template <typename DataType>
		void onData(DataHandlerType const& handler) {
			_handlers[typeid(DataType)] = handler;
		}

		std::thread run();

	private:
		ServerSocket _serverSocket;
		std::thread _masterThread;
		std::mutex _clientsMutex;
		std::vector<std::thread> _clients;
		DataHandlersType _handlers;
	};
}}
