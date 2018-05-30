//
//  Message.hpp
//  engine
//
//  Created by Arthur Chaloin on 11/05/2018.
//

#pragma once

#include <string>
#include <ctime>
#include <cstddef>
#include "engine/network/Network.hpp"

namespace engine { namespace network {

	struct __attribute__((packed)) Message {
		unsigned int size;
	};

	struct __attribute__((packed)) TextMessage : public Message {
		TextMessage(std::string const& text);

		char text[NET_MAX_MSG_SIZE - sizeof(Message)];
	};
}}
