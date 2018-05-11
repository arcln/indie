/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "EventsHandler.hpp"

engine::EventsReceiver::EventsReceiver(engine::Event<engine::KeyState>* keyEvents) : _keyEvents(keyEvents)
{
}

bool
engine::EventsReceiver::OnEvent(const irr::SEvent& event)
{
	_keyEvents->emit(engine::KeyState(event.KeyInput));
	return false;
}

engine::EventsHandler::EventsHandler() : keyEvents(), _eventReceiver(&keyEvents)
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
