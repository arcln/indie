/*
** EPITECH PROJECT, 2017
** arcade
** File description:
** A file for arcade
*/

#pragma once

#include <memory>
#include <string>
#include <dlfcn.h>
#include <cassert>
#include "engine/systems/System.hpp"

namespace engine {
	/**
	 * @brief Core helper to load libraries at runtime
	 * @tparam T Type of the instance to be loaded
	 */
	template<typename T>
	class DLLoader {
	public:

		/**
	 	 * @brief Load the pointed .so file
	 	 * @tparam T Type of the object returned by entry symbol
	 	 * @param lib Filename of the library to load
	 	 */
		explicit DLLoader(std::string const& lib);
		DLLoader() = default;
		DLLoader(DLLoader const&);
		DLLoader(DLLoader&&) noexcept = default;
		~DLLoader() = default;

		/**
		 * @brief Get the instance of the loaded object
		 * @return Smart pointer on the object
		 */
		std::unique_ptr<T>& instance();

		/**
		 * @brief Re-instanciate the object
		 */
		void reload();

		/**
		 * @brief Destroy the handle instance
		 */
		void close();

		using entrySymType = void* (*)();

	private:
		std::string __getEntrySymbolName() const;

		/**
		 * @brief Instance
		 */
		std::unique_ptr<T> _instance;

		/**
		 * @brief Loaded handle by call to dlopen()
		 */
		mutable void* _handle = nullptr;

		/**
		 * @brief Symbol used to instanciate the object
		 */
		entrySymType _entrySym = nullptr;
	};

	template<typename T>
	DLLoader<T>::DLLoader(std::string const& lib)
	{
		char* error = nullptr;

		_handle = dlopen(lib.c_str(), RTLD_NOW | RTLD_GLOBAL);
		if ((error = dlerror())) {
			throw std::runtime_error(error);
		}

		_entrySym = reinterpret_cast<entrySymType>(dlsym(_handle, __getEntrySymbolName().c_str()));
		if ((error = dlerror())) {
			throw std::runtime_error(error);
		}

		this->reload();
	}

	template<typename T>
	DLLoader<T>::DLLoader(DLLoader const& rhs)
	{
		_instance = std::move(rhs._instance);
		_entrySym = rhs._entrySym;
		_handle = rhs._handle;
		rhs._handle = nullptr;
	}

	template<typename T>
	std::unique_ptr<T>&
	DLLoader<T>::instance()
	{
		return _instance;
	}

	template<typename T>
	void
	DLLoader<T>::close()
	{
		if (_handle) {
			dlclose(_handle);
		}
	}

	template<typename T>
	void
	DLLoader<T>::reload()
	{
		void* ptr = _entrySym();
		assert(ptr);
		_instance = std::unique_ptr<T>(static_cast<T*>(ptr));
	}

	template<typename T>
	std::string
	DLLoader<T>::__getEntrySymbolName() const
	{
		return "instantiate";
	}
}
