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
#include <vector>
#include "engine/core/EntityId.hpp"

namespace engine {

	using GenericEvent = std::string;

	template <typename PayloadType, typename ResponseType = int>
	class Event {
	public:
		using ResponseCallbackType = std::function<void (ResponseType const&)>;
		using CallbackType = std::function<ResponseType (PayloadType const&)>;

		void emit(PayloadType const& payload, EntityId target = 0) {
			for (auto& sub : _subscribers[target]) {
				if (sub) {
					sub(payload);
				}
			}
		}

		void subscribe(CallbackType const& callback, std::size_t id = 0) {
			_subscribers[id].push_back(callback);
		}

		void unsubscribe(std::size_t id = 0) {
			auto sub = _subscribers.find(id);

			if (sub == std::end(_subscribers)) {
				throw std::runtime_error("specified event wasn't linked to entity " + std::to_string(id));
			}

			_subscribers.erase(sub);
		}

	protected:
		std::map<std::size_t, std::vector<CallbackType>> _subscribers;
	};
}
