/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "EventsHandler.hpp"

engine::EventsHandler::EventsHandler()
{
	keyEvents.subscribe([&](KeyState const& keyState) -> int {
		_keyStates[keyState.Key] = keyState;
		return 0;
	});
}

bool
engine::EventsHandler::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		keyEvents.emit(engine::KeyState(event.KeyInput));
	}
	return false;
}

engine::KeyState const&
engine::EventsHandler::getKeyState(KeyCode keyCode)
{
	return _keyStates[keyCode];
}
