/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "EventsHandler.hpp"

engine::EventsHandler::EventsHandler(Events& keyEvents) : _keyEvents(keyEvents)
{
	_registerEventTarget(Scene());
}

engine::KeyState const&
engine::EventsHandler::getKeyState(KeyCode keyCode)
{
	return _keyStates[keyCode];
}

void
engine::EventsHandler::unregisterEventTarget(Scene const& target)
{
	_keyEvents.erase(_keyEvents.find(target.id()));
}

void
engine::EventsHandler::_registerEventTarget(Scene const& target)
{
	_keyEvents[target.id()].subscribe([&](KeyState const& keyState) -> int {
		_keyStates[keyState.Key] = keyState;
		return 0;
	});
}

engine::EventsReceiver::EventsReceiver(Events& keyEvents) : _keyEvents(keyEvents)
{}

bool
engine::EventsReceiver::OnEvent(irr::SEvent const& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		for (auto& target : _keyEvents) {
			target.second.emit(engine::KeyState(event.KeyInput));
		}
	}

	return false;
}
