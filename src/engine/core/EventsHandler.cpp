/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "EventsHandler.hpp"

engine::EventsHandler::EventsHandler(KeyEvents& keyEvents, MouseMovedEvent& mouseMovedEvent) : _keyEvents(keyEvents), _mouseMovedEvent(mouseMovedEvent)
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

	_mouseMovedEvent.subscribe([&](MousePosition const& mousePosition) -> int {
		_mousePosition = mousePosition;
		return 0;
	});
}

void
engine::EventsHandler::enableKeyEvent(KeyCode code)
{
	_keyEventsState[code] = true;
}

void
engine::EventsHandler::disableKeyEvent(KeyCode code)
{
	_keyEventsState[code] = false;
}

bool
engine::EventsHandler::isKeyPressed(KeyCode code) const
{
	auto const& it = _keyEventsState.find(code);
	return it->second && it->first;
}

engine::MousePosition const&
engine::EventsHandler::getMousePosition() const
{
	return _mousePosition;
}

engine::EventsReceiver::EventsReceiver(KeyEvents& keyEvents, MouseMovedEvent& mouseMovedEvent)
	: _keyEvents(keyEvents)
	, _mouseMovedEvent(mouseMovedEvent)
{}

bool
engine::EventsReceiver::OnEvent(irr::SEvent const& event)
{
	switch (event.EventType) {
		case irr::EET_KEY_INPUT_EVENT:
			for (auto& target : _keyEvents) {
				target.second.emit(engine::KeyState(event.KeyInput), event.KeyInput.Key);
			}
			break;
		case irr::EET_MOUSE_INPUT_EVENT:
			_mouseMovedEvent.emit(engine::MousePosition(event.MouseInput.X, event.MouseInput.Y));
			break;
		default: break;
	}

	return false;
}
