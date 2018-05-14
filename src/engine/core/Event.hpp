/*
 ** EPITECH PROJECT, 2018
 ** worms
 ** File description:
 ** Event.hpp
 */

#pragma once

#include <iostream>
#include <vector>
#include <functional>

namespace engine {

	using GenericEvent = int;

	template <typename PayloadType, typename ResponseType = int>
	class Event {
	public:
		using ResponseCallbackType = std::function<void (ResponseType const&)>;
		using CallbackType = std::function<ResponseType (PayloadType const&)>;

		virtual ~Event() = default;

		virtual void emit(PayloadType const& payload, ResponseCallbackType const& callback) {
			for (auto& sub : _subscribers) {
				callback(sub(payload));
			}
		}

		virtual void emit(PayloadType const& payload) {
			this->emit(payload, [](ResponseType const&) {});
		}

		virtual void subscribe(CallbackType const& callback) {
			_subscribers.push_back(callback);
		}

	protected:
		std::vector<CallbackType> _subscribers;
	};
}
