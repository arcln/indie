/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include <iostream>
#include <sstream>
#include "Lua.hpp"

engine::Lua::Lua(std::string const& filename) : _state(luaL_newstate())
{
	if (luaL_loadfile(_state, filename.c_str()) || lua_pcall(_state, 0, 0, 0)) {
		throw std::runtime_error("Unable to load script");
	}

	luaL_openlibs(_state);
}

engine::Lua::~Lua()
{
	lua_close(_state);
}

void
engine::Lua::_cleanStack() const
{
	lua_pop(_state, lua_gettop(_state));
}

engine::Lua const&
engine::Lua::registerFunction(std::string const& name, std::function<int(lua_State*)> callback) const
{
	lua_pushcfunction(_state, callback.target<int (lua_State*)>());
	lua_setglobal(_state, name.c_str());
	return *this;
}

void
engine::Lua::_checkState(std::string const& message) const
{
	if (lua_isnil(_state, -1)) {
		throw std::runtime_error(message);
	}
}

void
engine::Lua::_putOnStack(std::string const& varPath) const
{
	std::stringstream tokens(varPath);
	std::string token;

	std::getline(tokens, token, '.');
	lua_getglobal(_state, token.c_str());
	_checkState(varPath + " not defined.");

	while (std::getline(tokens, token, '.')) {
		lua_getfield(_state, -1, token.c_str());
		_checkState(varPath + " not defined.");
	}
}

int
engine::Lua::getGlobal(std::string const& name) const
{
	return lua_getglobal(_state, name.c_str());
}

int
engine::Lua::pCall(int nargs, int nresults, int errFunc) const
{
	return lua_pcall(_state, nargs, nresults, errFunc);
}

namespace engine {

	template <>
	bool
	Lua::_getFromStack<bool>(std::string const& variable) const
	{
		return static_cast<bool>(lua_toboolean(_state, -1));
	}

	template <>
	int
	Lua::_getFromStack<int>(std::string const& variable) const
	{
		if (!lua_isnumber(_state, -1)) {
			throw std::runtime_error(variable + " isn't a number");
		}
		return static_cast<int>(lua_tonumber(_state, -1));
	}

	template <>
	float
	Lua::_getFromStack<float>(std::string const& variable) const
	{
		if (!lua_isnumber(_state, -1)) {
			throw std::runtime_error(variable + " isn't a number");
		}
		return static_cast<int>(lua_tonumber(_state, -1));
	}

	template <>
	std::string
	Lua::_getFromStack<std::string>(std::string const& variable) const
	{
		if (!lua_isstring(_state, -1)) {
			throw std::runtime_error(variable + " isn't a string");
		}
		return std::string(lua_tostring(_state, -1));
	}
}