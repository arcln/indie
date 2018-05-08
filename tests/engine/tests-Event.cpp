/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** main.cpp
*/

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "engine/Event.hpp"

TEST(Event, Basic_usage) {
	engine::Event<std::string, std::string> event;

	event.subscribe([](std::string const& payload) -> std::string {
		EXPECT_STREQ(payload.c_str(), "payload");
		return "response";
	});

	event.emit("payload", [](std::string const& response) -> void {
		EXPECT_STREQ(response.c_str(), "response");
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

	event.emit("payload", [](std::string const& response) -> void {
		EXPECT_STREQ(response.c_str(), "response");
	});
}

TEST(Event, Multiple_emit) {
	engine::Event<std::string, std::string> event;

	event.subscribe([](std::string const& payload) -> std::string {
		EXPECT_STREQ(payload.c_str(), "payload");
		return "response";
	});

	event.emit("payload", [](std::string const& response) -> void {
		EXPECT_STREQ(response.c_str(), "response");
	});

	event.emit("payload", [](std::string const& response) -> void {
		EXPECT_STREQ(response.c_str(), "response");
	});
}
