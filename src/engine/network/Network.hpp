//
//  Network.hpp
//  worms
//
//  Created by Arthur Chaloin on 11/05/2018.
//

#pragma once

#ifdef WIN32

#include <winsock2.h>

#define SOCKET_SIZE_TYPE	int

#else

#include <string>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCKET_SIZE_TYPE	unsigned
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif

#define NET_PORT			4290
#define NET_MAX_MSG_SIZE	4096
#define NET_MAX_CONNECTIONS	2

namespace engine { namespace network {
	static const std::string version = "v0.1";
}}