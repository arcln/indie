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

	enum EventConfig {
		EVT_RELEASE = 1 << 0,
		EVT_SYNCED = 1 << 1
	};

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
		void enableKeyEvent(KeyCode code);
		void disableKeyEvent(KeyCode code);

		template <typename PayloadType>
		void subscribe(engine::Scene& scene, engine::KeyCode key, std::string const& evt, PayloadType const& payload, int config = 0) {
			bool release = config & EventConfig::EVT_RELEASE;
			bool sync = config & EventConfig::EVT_SYNCED;

			_keyEvents[scene.id()].subscribe([this, &scene, evt, payload, key, sync, release](engine::KeyState const& k) -> int {
				if (k.Key == key && release ^ k.PressedDown && scene.hasEvent(evt) && _keyEventsState[key]) {
					if (sync) {
						scene.triggerSyncedEvent(evt, payload.serialize());
					} else {
						scene.triggerEvent<PayloadType>(evt, payload);
					}
				}

				return 0;
			});

			_keyEventsState[key] = true;
		}

	private:
		std::unordered_map<KeyCode, KeyState, EnumClassHash> _keyStates;
		Events& _keyEvents;
		std::unordered_map<KeyCode, bool> _keyEventsState;

		void _registerEventTarget(Scene const& target);
	};
}
