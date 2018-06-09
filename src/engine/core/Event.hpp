/*
 ** EPITECH PROJECT, 2018
 ** worms
 ** File description:
 ** Event.hpp
 */

#pragma once

#include <iostream>
#include <map>
#include <functional>

namespace engine {

	using GenericEvent = std::string;

	template <typename PayloadType, typename ResponseType = int>
	class Event {
	public:
		using ResponseCallbackType = std::function<void (ResponseType const&)>;
		using CallbackType = std::function<ResponseType (PayloadType const&)>;

		void emit(PayloadType const& payload, ResponseCallbackType const& callback) {
			for (auto& sub : _subscribers) {
				callback(sub.second(payload));
			}
		}

		void emit(PayloadType const& payload) {
			this->emit(payload, [](ResponseType const&) {});
		}

		void subscribe(CallbackType const& callback, std::size_t id = 0) {
			_subscribers[id] = callback;
		}

		void unsubscribe(std::size_t id = 0) {
			auto sub = _subscribers.find(id);

			if (sub == std::end(_subscribers)) {
				throw std::runtime_error("specified event wasn't linked to entity " + std::to_string(id));
			}

			_subscribers.erase(sub);
		}

	protected:
		std::map<std::size_t, CallbackType> _subscribers;
	};
}
