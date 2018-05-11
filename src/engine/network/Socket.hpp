//
//  Socket.hpp
//  engine
//
//  Created by Arthur Chaloin on 10/05/2018.
//

#pragma once

#include "engine/network/Network.hpp"
#include "engine/network/Message.hpp"

namespace engine { namespace network {

	class Socket {
	public:
		Socket();
		~Socket();

		Socket& create();
		Socket const& bind() const;
		Socket const& listen() const;
		Socket const& accept(Socket& socket) const;
		Socket const& connect(std::string const& hostname) const;

		template <typename MessageType>
		void send(MessageType const& data) const {
			if (::send(_socket, &data, sizeof(MessageType), 0) < 0) {
				throw std::runtime_error("failed to write into socket.");
			}
		}

		template <typename MessageType>
		MessageType receive() const {
			char buffer[NET_MAX_MSG_SIZE];
			if (::recv(_socket, buffer, NET_MAX_MSG_SIZE, 0) < 0) {
				throw std::runtime_error("failed to read into socket.");
			}

			auto data = *reinterpret_cast<MessageType*>(buffer);
			if (data.size != sizeof(MessageType)) {
				throw std::runtime_error("corrupted packet");
			}

			return data;
		}

	private:
		SOCKET _socket;
	};

	class ServerSocket : public Socket {
	public:
		ServerSocket();
	};

	class ClientSocket : public Socket {};
}}
