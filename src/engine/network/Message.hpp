//
//  Message.hpp
//  engine
//
//  Created by Arthur Chaloin on 11/05/2018.
//

#pragma once

#include <cstddef>
#include <string>

namespace engine { namespace network {

	struct Message {
		unsigned int size;
	};

	struct TextMessage : public Message {
		char text[256];
	};
}}
