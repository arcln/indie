//
//  Vector.hpp
//  engine
//
//  Created by Arthur Chaloin on 30/05/2018.
//

#pragma once

#include <irrlicht/irrlicht.h>
#include "EventPayload.hpp"

namespace worms {

	template <typename DataType>
	struct Vector2 : public EventPayload {
		explicit Vector2(DataType x = 0, DataType y = 0) : x(x), y(y) {}
		explicit Vector2(std::string const& data) {
			this->unserialize(data);
		}

		operator irr::core::vector2d<DataType>() const {
			return irr::core::vector2d<DataType> {x, y};
		}

		std::string serialize() const override {
			return std::to_string(this->x) + ";" + std::to_string(this->y);
		}

		void unserialize(std::string const& data) override {
			try {
				this->x = std::stof(data);
				this->y = std::stof(data.substr(data.find(';') + 1));
			} catch (std::exception& e) {
				this->x = 0;
				this->y = 0;
				std::cerr << "[worms]: warning: unserializing failed (" << __PRETTY_FUNCTION__ << ")" << std::endl;
			}
		}

		DataType x;
		DataType y;
	};

	template <typename DataType>
	struct Vector3 : public EventPayload {
		explicit Vector3(DataType x = 0, DataType y = 0, DataType z = 0) : x(x), y(y), z(z) {}
		explicit Vector3(std::string const& data) {
			this->unserialize(data);
		}

		operator irr::core::vector3d<DataType>() const {
			return irr::core::vector3d<DataType> {x, y, z};
		}

		std::string serialize() const override {
			return std::to_string(this->x) + ";"
				 + std::to_string(this->y) + ";"
				 + std::to_string(this->z);
		}

		void unserialize(std::string const& data) override {
			try {
				const std::size_t offset = data.find(';') + 1;

				this->x = std::stof(data);
				this->y = std::stof(data.substr(offset));
				this->z = std::stof(data.substr(data.find(';', offset) + 1));
			} catch (std::exception& e) {
				this->x = 0;
				this->y = 0;
				this->z = 0;
				std::cerr << "[worms]: warning: unserializing failed (" << __PRETTY_FUNCTION__ << ")" << std::endl;
			}
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
