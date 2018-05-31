//
//  Vector.hpp
//  engine
//
//  Created by Arthur Chaloin on 30/05/2018.
//

#pragma once

#include "EventPayload.hpp"

namespace worms {

	template <typename DataType>
	struct Vector2 : public EventPayload {
		DataType x;
		DataType y;
	};

	template <typename DataType>
	struct Vector3 : public EventPayload {
		explicit Vector3(DataType x = 0, DataType y = 0, DataType z = 0) : x(x), y(y), z(z) {}

		std::string serialize() const override {
			return std::to_string(this->x) + ";"
				 + std::to_string(this->y) + ";"
				 + std::to_string(this->z);
		}

		void unserialize(std::string const& data) override {
			const std::size_t offset = data.find(';') + 1;

			this->x = std::stof(data);
			this->y = std::stof(data.substr(offset));
			this->z = std::stof(data.substr(data.find(';', offset) + 1));
		}

		DataType x;
		DataType y;
		DataType z;
	};

	using Vector2i = Vector2<int>;
	using Vector2u = Vector2<unsigned>;
	using Vector2f = Vector2<float>;
	using Vector3i = Vector3<int>;
	using Vector3u = Vector3<unsigned>;
	using Vector3f = Vector3<float>;
}
