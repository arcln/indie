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
#include "engine/core/Scene.hpp"

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
	using Events = std::map<std::size_t, Event<KeyState>>;

	class EventsReceiver : public irr::IEventReceiver {
	public:
		explicit EventsReceiver(Events& keyEvents);

		bool OnEvent(irr::SEvent const& event) override;

	private:
		Events& _keyEvents;
	};

	class EventsHandler {
	public:
		explicit EventsHandler(Events& keyEvents);

		KeyState const& getKeyState(KeyCode keyCode);

		void unregisterEventTarget(Scene const& target);

		template <typename PayloadType>
		void subscribe(engine::Scene& scene, engine::KeyCode key, std::string const& evt, PayloadType const& payload, bool onRelease = false) {
			_keyEvents[scene.id()].subscribe([&scene, evt, payload, key, onRelease](engine::KeyState const& k) -> int {
				if (k.Key == key && onRelease ^ k.PressedDown && scene.hasEvent(evt)) {
					scene.triggerEvent<PayloadType>(evt, payload);
				}

				return 0;
			});
		}

	private:
		std::unordered_map<KeyCode, KeyState, EnumClassHash> _keyStates;
		Events& _keyEvents;

		void _registerEventTarget(Scene const& target);
	};
}
