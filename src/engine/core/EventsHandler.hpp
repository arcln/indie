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
	using Events = std::unordered_map<std::size_t, Event<KeyState>>;

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
		void subscribe(engine::Scene& scene, engine::KeyCode key, std::string const& evt, EntityId target, PayloadType const& payload, int config = 0) {
			bool release = config & EventConfig::EVT_RELEASE;
			bool sync = config & EventConfig::EVT_SYNCED;

			_keyEvents[scene.id()].subscribe([this, &scene, evt, target, payload, key, sync, release](engine::KeyState const& k) -> int {
				if (k.Key == key && release ^ k.PressedDown && scene.hasEvent(evt) && _keyEventsState[key]) {
					_bootstrapEvent<PayloadType>(scene, evt, payload, target, sync);
				}

				return 0;
			}, target);

			_keyEventsState[key] = true;
		}

	private:
		std::unordered_map<KeyCode, KeyState, EnumClassHash> _keyStates;
		Events& _keyEvents;
		std::unordered_map<KeyCode, bool, EnumClassHash> _keyEventsState;

		template <typename PayloadType>
		using IsString = typename std::enable_if<std::is_same<std::string, PayloadType>::value, PayloadType>::type;

		template <typename PayloadType>
		using IsNotString = typename std::enable_if<!std::is_same<std::string, PayloadType>::value, PayloadType>::type;

		template <typename PayloadType>
		void _bootstrapEvent(Scene& scene, std::string const& evt, IsString<PayloadType> const& payload, EntityId target, bool synced) {
			if (synced) {
				scene.triggerSyncedEvent(evt, target, payload);
			} else {
				scene.triggerEvent<PayloadType>(evt, target, payload);
			}
		}

		template <typename PayloadType>
		void _bootstrapEvent(Scene& scene, std::string const& evt, IsNotString<PayloadType> const& serializablePayload, EntityId target, bool synced) {
			if (synced) {
				scene.triggerSyncedEvent(evt, target, serializablePayload.serialize());
			} else {
				scene.triggerEvent<PayloadType>(evt, target, serializablePayload);
			}
		}

		void _registerEventTarget(Scene const& target);
	};
}
