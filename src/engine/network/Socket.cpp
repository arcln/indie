//
//  Socket.cpp
//  engine
//
//  Created by Arthur Chaloin on 10/05/2018.
//

#include <iostream>
#include "Socket.hpp"

engine::network::Socket::Socket() = default;

engine::network::Socket const&
engine::network::Socket::connect(std::string const& hostname) const
{
	struct hostent *hostinfo = nullptr;
	SOCKADDR_IN sin;

	hostinfo = gethostbyname(hostname.c_str());
	if (hostinfo == nullptr) {
		throw std::runtime_error("failed to resolve host '" + hostname + "'");
	}

	sin.sin_addr = *reinterpret_cast<IN_ADDR*>(hostinfo->h_addr);
	sin.sin_port = htons(NET_PORT);
	sin.sin_family = AF_INET;

	if (::connect(_socket, reinterpret_cast<SOCKADDR*>(&sin), sizeof(SOCKADDR)) == SOCKET_ERROR) {
		throw std::runtime_error("failed to etablish connection");
	}

	return *this;
}

engine::network::Socket&
engine::network::Socket::create()
{
	_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (_socket == INVALID_SOCKET) {
		throw std::runtime_error("failed to create socket");
	}

	return *this;
}

engine::network::Socket const&
engine::network::Socket::bind() const
{
	SOCKADDR_IN sin;

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(NET_PORT);

	if (::bind(_socket,reinterpret_cast<SOCKADDR*>(&sin), sizeof sin) == SOCKET_ERROR) {
		throw std::runtime_error("failed to bind socket. is the port already in use?");
	}

	return *this;
}

engine::network::Socket const&
engine::network::Socket::listen() const
{
	if (::listen(_socket, NET_MAX_CONNECTIONS) == SOCKET_ERROR) {
		throw std::runtime_error("failed to start listening");
	}

	return *this;
}

engine::network::Socket const&
engine::network::Socket::accept(Socket& client) const
{
	SOCKADDR_IN csin;
	unsigned sinsize = sizeof csin;

	client._socket = ::accept(_socket, reinterpret_cast<SOCKADDR*>(&csin), &sinsize);

	if (client._socket == INVALID_SOCKET) {
		throw std::runtime_error("failed to accept connection");
	}

	return *this;
}

template<>
void
engine::network::Socket::send<std::string>(std::string const& data) const
{
	TextMessage msg;

	msg.size = sizeof(TextMessage);
	std::sprintf(msg.text, "%s", data.c_str());
	this->send<TextMessage>(msg);
}

engine::network::Socket&
engine::network::Socket::destroy()
{
	closesocket(_socket);
	return *this;
}

engine::network::ServerSocket::ServerSocket()
{
	this->create().bind().listen();
}
