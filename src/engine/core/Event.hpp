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

	template <typename PayloadType, typename ResponseType = int>
	class Event {
	public:
		using ResponseCallbackType = std::function<void (ResponseType const&)>;
		using CallbackType = std::function<ResponseType (PayloadType const&)>;

		void emit(PayloadType const& payload, ResponseCallbackType const& callback) {
			for (auto& sub : _subscribers) {
				callback(sub(payload));
			}
		}

		void emit(PayloadType const& payload) {
			this->emit(payload, [](ResponseType const&) {});
		}

		void subscribe(CallbackType const& callback) {
			_subscribers.push_back(callback);
		}

	private:
		std::vector<CallbackType> _subscribers;
	};
}
