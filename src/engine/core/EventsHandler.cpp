/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "EventsHandler.hpp"

engine::EventsHandler::EventsHandler(Event<KeyState>& keyEvents) : _keyEvents(keyEvents)
{
	keyEvents.subscribe([&](KeyState const& keyState) -> int {
		_keyStates[keyState.Key] = keyState;
		return 0;
	});
}

engine::KeyState const&
engine::EventsHandler::getKeyState(KeyCode keyCode)
{
	return _keyStates[keyCode];
}

void
engine::EventsHandler::subscribe(engine::Event<engine::KeyState>::CallbackType const& callback)
{
	_keyEvents.subscribe(callback);
}

engine::EventsReceiver::EventsReceiver(engine::Event<engine::KeyState>& keyEvents) : _keyEvents(keyEvents)
{}

bool
engine::EventsReceiver::OnEvent(irr::SEvent const& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		_keyEvents.emit(engine::KeyState(event.KeyInput));
	}

	return false;
}
