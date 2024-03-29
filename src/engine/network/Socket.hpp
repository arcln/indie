//
//  Socket.hpp
//  engine
//
//  Created by Arthur Chaloin on 10/05/2018.
//

#pragma once

#include <cstring>
#include "engine/network/Network.hpp"
#include "engine/network/Message.hpp"

namespace engine { namespace network {

	class Socket {
	public:
		Socket();

		Socket& create();
		Socket& destroy();
		Socket const& bind() const;
		Socket const& listen() const;
		Socket const& accept(Socket& socket) const;
		Socket const& connect(std::string const& hostname) const;

		template <typename MessageType>
		void send(MessageType const& data) const {
			auto dataCpy = data;
			dataCpy.size = sizeof(MessageType);
			if (::send(_socket, reinterpret_cast<char *>(&dataCpy), sizeof(MessageType), 0) < 0) {
				throw std::runtime_error(std::string("failed to write into socket (") + strerror(errno) + ")");
			}
		}

		template <typename MessageType>
		MessageType receive() const {
			char buffer[NET_MAX_MSG_SIZE];
			long recvSize = 0;

			if ((recvSize = ::recv(_socket, buffer, NET_MAX_MSG_SIZE, 0)) < 0) {
				throw std::runtime_error(std::string("failed to read into socket (") + strerror(errno) + ")");
			} else if (recvSize == 0) {
				throw std::runtime_error("connection was closed by remote host");
			}

			auto data = reinterpret_cast<MessageType*>(buffer);
			if (data->size != sizeof(MessageType)) {
				std::cerr << "warning: ignoring corrupted packet (size " << data->size << ")" << std::endl;
				return MessageType();
			}

			return *data;
		}

	private:
		SOCKET _socket;
	};

	class ServerSocket : public Socket {
	public:
		ServerSocket();
	};

	class ClientSocket : public Socket {
	public:
		ClientSocket();

		std::size_t id;

	private:
		static std::size_t _NextId;
	};
}}
