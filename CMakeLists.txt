cmake_minimum_required(VERSION 2.8)
project(worms)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Wno-unused-parameter -g -O2")

find_package(Threads REQUIRED)

if (WIN32)
	set(CMAKE_CXX_FLAGS "/EHsc /DWIN32")
	set(ZLIB_INCLUDE_DIR "")
	set(GLUT_INCLUDE_DIR "")
	include_directories(vendor)
else (WIN32)
	find_package(GLUT REQUIRED)
	find_package(OpenGL REQUIRED)
	find_package(ZLIB REQUIRED)
	find_package(GTest REQUIRED)

	if (APPLE)
		find_library(COCOA_LIBRARY Cocoa REQUIRED)
		find_library(IOKIT_LIBRARY IOKit REQUIRED)
		find_library(APPKIT_LIBRARY AppKit REQUIRED)
	endif (APPLE)
endif (WIN32)

if (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

if (CMAKE_CXX_FLAGS_DEBUG)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

	if (NOT WIN32)
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
	endif (NOT WIN32)
else (CMAKE_CXX_FLAGS_DEBUG)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/release)
endif (CMAKE_CXX_FLAGS_DEBUG)

link_directories(/usr/local/lib)
include_directories(
	${OPENGL_INCLUDE_DIR}
	${GLUT_INCLUDE_DIR}
	${ZLIB_INCLUDE_DIR}
	${IOKIT_INCLUDE_DIR}
	${COCOA_INCLUDE_DIR}
	${GTEST_INCLUDE_DIRS}
	./src
)

file(GLOB_RECURSE GAME_SRCS src/game/*)
file(GLOB_RECURSE ENGINE_SRCS src/engine/*)

add_library(engine STATIC ${ENGINE_SRCS})

add_executable(worms src/main.cpp ${GAME_SRCS})
set_target_properties(worms PROPERTIES COMPILE_FLAGS "-DWORMS_IS_SERVER=false")

add_executable(worms-server src/main.cpp ${GAME_SRCS})
set_target_properties(worms-server PROPERTIES COMPILE_FLAGS "-DWORMS_IS_SERVER=true")

target_link_libraries(worms
	${OPENGL_LIBRARIES}
	${COCOA_LIBRARY}
	${APPKIT_LIBRARY}
	${IOKIT_LIBRARY}
	${GLUT_LIBRARIES}
	${ZLIB_LIBRARIES}
	engine pthread Irrlicht
)

target_link_libraries(worms-server
	${OPENGL_LIBRARIES}
	${COCOA_LIBRARY}
	${APPKIT_LIBRARY}
	${IOKIT_LIBRARY}
	${GLUT_LIBRARIES}
	${ZLIB_LIBRARIES}
	engine pthread Irrlicht
)

if (NOT WIN32)
	add_subdirectory(tests)
endif (NOT WIN32)
