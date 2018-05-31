//
//  Message.cpp
//  engine
//
//  Created by Arthur Chaloin on 30/05/2018.
//

#include <cstdio>
#include "Message.hpp"

engine::network::TextMessage::TextMessage(std::string const& data)
{
	std::sprintf(this->text, "%s", data.c_str());
}
