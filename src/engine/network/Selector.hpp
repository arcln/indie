//
//  Selector.hpp
//  engine
//
//  Created by Arthur Chaloin on 11/05/2018.
//

#pragma once

#include <vector>
#include <thread>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include "engine/network/Socket.hpp"
#include "engine/network/Socket.hpp"

namespace engine { namespace network {

	class Selector {
	public:
		template <typename DataType>
		using DataHandlerType = std::function<void (ClientSocket const&, DataType const&)>;

		template <typename DataType>
		void onData(DataHandlerType<DataType> const& handler) {
			_handlers[typeid(DataType)] = handler;
		}

		void run();

	private:
		ServerSocket _serverSocket;
		std::vector<std::pair<ClientSocket, std::thread>> _clients;
		std::unordered_map<std::type_index, std::function<void ()>> _handlers;
	};
}}
