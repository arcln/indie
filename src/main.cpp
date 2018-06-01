/*
** EPITECH PROJECT, 2018
** worms
** File description:
** main.cpp
*/

#include "engine/Engine.hpp"
#include "game/Worms.hh"

#ifndef APPLE
# define ENGINE_OS_SETUP	""
#endif

#ifdef APPLE
# include <IOKit/IOCFBundle.h>

# define ENGINE_OS_SETUP	__osxGetCwd()

char const* __osxGetCwd()
{
	CFURLRef appUrlRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
	CFStringRef macPath = CFURLCopyFileSystemPath(appUrlRef, kCFURLPOSIXPathStyle);
	char const* pathPtr = CFStringGetCStringPtr(macPath, kCFStringEncodingUTF8);

	CFRelease(appUrlRef);
	CFRelease(macPath);
	return pathPtr;
}

#endif

#ifdef WIN32
# include <winsock2.h>
# pragma comment(lib, "Ws2_32.lib")

void __win32InitSockets()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
}

#endif

int main()
{
#ifdef WIN32
	__win32InitSockets();
#endif

	engine::Engine engine(WORMS_IS_SERVER, ENGINE_OS_SETUP);
	auto status = engine.play(worms::worms);

#ifdef WIN32
	WSACleanup();
#endif

	return status;
}
