cmake_minimum_required(VERSION 3.9)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")

add_executable(bomberman
	src/main.cpp
)
