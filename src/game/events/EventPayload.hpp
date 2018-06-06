//
//  EventPayload.hpp
//  engine
//
//  Created by Arthur Chaloin on 31/05/2018.
//

#pragma once

#include <string>

namespace worms {

	class EventPayload {
	public:
		virtual std::string serialize() const = 0;
		virtual void unserialize(std::string const& data) = 0;
	};
}
