/*
** EPITECH PROJECT, 2018
** worms
** File description:
** main.cpp
*/

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "engine/core/Event.hpp"

TEST(Event, Basic_usage) {
	engine::Event<std::string, std::string> event;

	event.subscribe([](std::string const& payload) -> std::string {
		EXPECT_STREQ(payload.c_str(), "payload");
		return "response";
	});
}

TEST(Event, Multiple_sub) {
	engine::Event<std::string, std::string> event;

	event.subscribe([](std::string const& payload) -> std::string {
		EXPECT_STREQ(payload.c_str(), "payload");
		return "response";
	});

	event.subscribe([](std::string const& payload) -> std::string {
		EXPECT_STREQ(payload.c_str(), "payload");
		return "response";
	});
}

TEST(Event, Multiple_emit) {
	engine::Event<std::string, std::string> event;

	event.subscribe([](std::string const& payload) -> std::string {
		EXPECT_STREQ(payload.c_str(), "payload");
		return "response";
	});
}

TEST(Event, No_response) {
	engine::Event<std::string> event;

	event.subscribe([](std::string const& payload) -> int {
		EXPECT_STREQ(payload.c_str(), "payload");
		return 0;
	});

	event.emit("payload");
}
