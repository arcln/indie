/*
** EPITECH PROJECT, 2017
** arcade
** File description:
** A file for arcade
*/

#pragma once

#include <string>
#include <future>
#include <functional>
#include <fstream>
#include <unordered_map>
#include <iostream>

/**
 * @brief Engine namespace, used for everything that touch to low-level graphics
 */
namespace engine {

	using MeshNode = irr::scene::IAnimatedMesh;
	using Texture = irr::video::ITexture;

	/**
	 * @brief Provided ressource manager for libraries
	 * @tparam T Resource to be managed
	 */
	template<typename T>
	class ResourceManager {
	public:
		~ResourceManager() = default;

		using LoadFuncType = T (std::string const&);
		using Callback = std::function<void (bool)>;

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
		ResourceManager<T>& onLoad(std::function<LoadFuncType> const& loadFunc) {
			_loadFunc = loadFunc;
			return *this;
		}

		ResourceManager<T>& loadFrom(std::string const& root) {
			_root = root;
			return *this;
		}

		bool syncLoad(std::vector<std::string> const& files) {
			try {
				for (auto& file : files) {
					this->get(file);
				}
			} catch (std::exception& e) {
				std::cerr << "worms: " << e.what() << std::endl;
				return true;
			}

			return false;
		}

		std::future<bool> asyncLoad(std::vector<std::string> const& files) {
			return std::async(std::launch::async, [this](std::vector<std::string> const& files) -> bool {
				return this->syncLoad(files);
			}, files);
		}

		static ResourceManager<T>& instance() {
			static ResourceManager<T> inst;

			return inst;
		}

	private:
		ResourceManager() = default;
		ResourceManager(ResourceManager const&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator =(ResourceManager const&) = delete;
		ResourceManager& operator =(ResourceManager&&) = delete;

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
