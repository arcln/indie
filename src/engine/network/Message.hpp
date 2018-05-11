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

	struct Message {
		unsigned int size;
	};

	struct TextMessage : public Message {
		char text[NET_MAX_MSG_SIZE - sizeof(Message)];
	};
}}
