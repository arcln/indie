cmake_minimum_required(VERSION 2.8)
project(worms)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Wno-unused-parameter -g")

find_package(Threads REQUIRED)
find_package(GLUT REQUIRED)
find_package(ZLIB REQUIRED)
find_package(GTest REQUIRED)
find_package(OpenGL REQUIRED)

if (APPLE)
	find_library(COCOA_LIBRARY Cocoa REQUIRED)
	find_library(IOKIT_LIBRARY IOKit REQUIRED)
	find_library(APPKIT_LIBRARY AppKit REQUIRED)
endif (APPLE)

if (WIN32)
	set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
	find_package(X11 REQUIRED)
endif (WIN32)

if (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

if (CMAKE_CXX_FLAGS_DEBUG)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
else (CMAKE_CXX_FLAGS_DEBUG)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/release)
endif (CMAKE_CXX_FLAGS_DEBUG)

file(GLOB_RECURSE GAME_SRCS src/game/*)

include_directories(
	${OPENGL_INCLUDE_DIR}
	${X11_INCLUDE_DIR}
	${GLUT_INCLUDE_DIR}
	${ZLIB_INCLUDE_DIR}
	${IOKIT_INCLUDE_DIR}
	${COCOA_INCLUDE_DIR}
	${GTEST_INCLUDE_DIRS}
	./src
)

link_directories(/usr/local/lib)

file(GLOB_RECURSE ENGINE_SRCS src/engine/*)
add_library(engine STATIC ${ENGINE_SRCS} src/engine/components/LightComponent.cpp src/engine/components/LightComponent.hpp)

add_executable(worms src/client.cpp ${GAME_SRCS})
target_link_libraries(worms
	Irrlicht
	${OPENGL_LIBRARIES}
	${COCOA_LIBRARY}
	${APPKIT_LIBRARY}
	${IOKIT_LIBRARY}
	${X11_LIBRARIES}
	${GLUT_LIBRARIES}
	${ZLIB_LIBRARIES}
	engine pthread
)

add_executable(worms-server src/server.cpp ${GAME_SRCS})
target_link_libraries(worms-server
	Irrlicht
	${OPENGL_LIBRARIES}
	${COCOA_LIBRARY}
	${APPKIT_LIBRARY}
	${IOKIT_LIBRARY}
	${X11_LIBRARIES}
	${GLUT_LIBRARIES}
	${ZLIB_LIBRARIES}
	engine pthread
)

add_subdirectory(tests)
