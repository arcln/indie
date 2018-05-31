/*
** EPITECH PROJECT, 2018
** worms
** File description:
** main.cpp
*/

#include "engine/Engine.hpp"
#include "game/Worms.hh"

#ifdef WIN32

#pragma comment(lib, "Ws2_32.lib")

#include <winsock2.h>

void __initWin32Sockets()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
}

#endif

int main()
{
#ifdef WIN32
	__initWin32Sockets();
#endif

	engine::Engine engine(WORMS_IS_SERVER);
	auto status = engine.play(worms::worms);

#ifdef WIN32
	WSACleanup();
#endif

	return status;
}
