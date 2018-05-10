cmake_minimum_required(VERSION 2.8)
project(worms)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")

find_package(Threads REQUIRED)
find_package(GLUT REQUIRED)
find_package(ZLIB REQUIRED)
find_package(GTest REQUIRED)

if (APPLE)
	find_package(OpenGl)
endif (APPLE)

if (WIN32)
	set(CMAKE_CXX_FLAGS "")
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

include_directories(
	${OPENGL_INCLUDE_DIR}
	${X11_INCLUDE_DIR}
	${GLUT_INCLUDE_DIR}
	${ZLIB_INCLUDE_DIR}
	${IOKIT_INCLUDE_DIR}
	${GTEST_INCLUDE_DIRS}
	./src
)

link_directories(/usr/local/lib)

if (APPLE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework IOKit")
endif (APPLE)

enable_testing()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-arcs -ftest-coverage")
file(GLOB_RECURSE TESTS_SRCS ./*)
add_executable(tests-engine ${TESTS_SRCS})
target_link_libraries(tests-engine
	engine pthread Irrlicht
	${OPENGL_LIBRARIES}
	${X11_LIBRARIES}
	${GLUT_LIBRARIES}
	${ZLIB_LIBRARIES}
	${IOKIT_LIBRARIES}
	${GTEST_BOTH_LIBRARIES}
)
