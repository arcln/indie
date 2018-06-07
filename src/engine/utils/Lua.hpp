/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include <functional>

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

namespace engine {

	class Lua {
	public:
		Lua() = default;
		explicit Lua(std::string const& filename);
		~Lua();

		template <typename Data>
		Data get(std::string const& variable) const {
			Data result;

			this->_putOnStack(variable);
			result = _getFromStack<Data>(variable);

			_cleanStack();
			return result;
		}

		Lua const& registerFunction(std::string const& name, std::function<int(lua_State*)> callback) const;

		int getGlobal(std::string const& name) const;
		int pCall(int nargs, int nresults, int errFunc) const;

	private:
		lua_State* _state;

		void _checkState(std::string const& message) const;
		void _putOnStack(std::string const& varPath) const;
		void _cleanStack() const;

		template <typename Data>
		Data _getFromStack(std::string const& variable) const {
			throw std::runtime_error(typeid(Data).name());
		}
	};
}


