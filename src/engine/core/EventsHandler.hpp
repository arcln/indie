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

	class EventsHandler : public irr::IEventReceiver {
	public:
		EventsHandler();

		bool OnEvent(const irr::SEvent& event) override;

		KeyState const& getKeyState(KeyCode keyCode);

		Event<KeyState> keyEvents;
	private:
		std::unordered_map<KeyCode, KeyState, EnumClassHash> _keyStates;
	};
}
