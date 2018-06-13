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
		EVT_RELEASE		= 1 << 0,
		EVT_SYNCED 		= 1 << 1,
		EVT_OVERRIDE 	= 1 << 2
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
	using MousePosition = irr::core::vector2d<irr::s32>;

	using KeyEvents = std::unordered_map<std::size_t, Event<KeyState>>;
	using MouseMovedEvent = Event<MousePosition>;

	class EventsReceiver : public irr::IEventReceiver {
	public:
		EventsReceiver(KeyEvents& keyEvents, MouseMovedEvent& mouseMovedEvent);

		bool OnEvent(irr::SEvent const& event) override;

	private:
		KeyEvents& _keyEvents;
		MouseMovedEvent& _mouseMovedEvent;
	};

	class EventsHandler {
	public:
		EventsHandler(KeyEvents& keyEvents, MouseMovedEvent& _mouseMovedEvent);

		KeyState const& getKeyState(KeyCode keyCode);
		MousePosition const& getMousePosition() const;

		void unregisterEventTarget(Scene const& target);
		void enableKeyEvent(KeyCode code);
		void disableKeyEvent(KeyCode code);

		bool isKeyPressed(KeyCode code) const;

		template <typename PayloadType>
		void subscribe(engine::Scene& scene, engine::KeyCode key, std::string const& evt, EntityId target, PayloadType const& payload, int config = 0) {
			bool release = config & EventConfig::EVT_RELEASE;
			bool sync = config & EventConfig::EVT_SYNCED;

			if (config & EventConfig::EVT_OVERRIDE) {
				try {
					_keyEvents[scene.id()].unsubscribe(key);
				} catch (std::exception&) {}
			}

			_keyEvents[scene.id()].subscribe([this, &scene, evt, target, payload, key, sync, release](engine::KeyState const& k) -> int {
				if (k.PressedDown && _keyStates[key].PressedDown) {
					_keyStates[key] = k;
					return 0;
				}

				if (release ^ k.PressedDown && scene.hasEvent(evt) && _keyEventsState[key]) {
					_bootstrapEvent<PayloadType>(scene, evt, payload, target, sync);
				}

				_keyStates[key] = k;
				return 0;
			}, key);

			_keyEventsState[key] = true;
		}

	private:
		std::unordered_map<KeyCode, KeyState, EnumClassHash> _keyStates;
		KeyEvents& _keyEvents;
		std::unordered_map<KeyCode, bool, EnumClassHash> _keyEventsState;

		MouseMovedEvent& _mouseMovedEvent;
		MousePosition _mousePosition;

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
