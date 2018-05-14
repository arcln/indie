/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <unordered_map>
#include <functional>
#include <irrlicht/IEventReceiver.h>
#include "Event.hpp"

namespace engine {

	struct EnumClassHash {
		template <typename T>
		std::size_t operator()(T t) const
		{
			return static_cast<std::size_t>(t);
		}
	};

	using KeyCode = irr::EKEY_CODE;

	using KeyState = irr::SEvent::SKeyInput;

	class EventsReceiver : public irr::IEventReceiver {
	public:
		explicit EventsReceiver(Event<KeyState>& keyEvents);

		bool OnEvent(irr::SEvent const& event) override;

	private:
		Event<KeyState>& _keyEvents;
	};

	class EventsHandler {
	public:
		explicit EventsHandler(Event<KeyState>& keyEvents);

		KeyState const& getKeyState(KeyCode keyCode);

		void subscribe(Event<KeyState>::CallbackType const& callback);

	private:
		std::unordered_map<KeyCode, KeyState, EnumClassHash> _keyStates;
		Event<KeyState>& _keyEvents;
	};
}
