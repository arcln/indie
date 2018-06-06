/*
** EPITECH PROJECT, 2017
** arcade
** File description:
** A file for arcade
*/

#pragma once

#include <string>
#include <functional>
#include <fstream>
#include <unordered_map>
#include <iostream>

/**
 * @brief Engine namespace, used for everything that touch to low-level graphics
 */
namespace engine {

	/**
	 * @brief Provided ressource manager for libraries
	 * @tparam T Resource to be managed
	 */
	template<typename T>
	class ResourceManager {
	public:
		explicit ResourceManager(std::string const& root) : _root(root) {}
		~ResourceManager() = default;

		using LoadFuncType = T (std::string const&);

		/**
		 * @brief Get the requested resource. Automaticaly loads from disk if asset isn't found in cache
		 * @param asset Path to the asset to load
		 * @return Requested resource
		 */
		T const& get(std::string const& asset) {
			if (_cache.find(asset) == _cache.end()) {
				_cache[asset] = _loadFunc(_root + asset);
			}

			return _cache[asset];
		}

		/**
		 * @brief Define the function that will be used to load the resource
		 * @param loadFunc Conversion function from raw data to T
		 */
		void onLoad(std::function<LoadFuncType> const& loadFunc) {
			_loadFunc = loadFunc;
		}

	private:
		/**
		 * @brief Resources cache
		 */
		std::unordered_map<std::string, T> _cache;

		/**
		 * @brief Conversion function
		 */
		std::function<LoadFuncType> _loadFunc;

		/**
		 * @brief Stream to read from filesystem
		 */
		std::ifstream _file;

		/**
		 * @brief Base dir
		 */
		std::string _root;
	};
}
