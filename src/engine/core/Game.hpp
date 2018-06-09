/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <list>
#include <stack>
#include <vector>
#include <unordered_map>
#include <irrlicht/irrlicht.h>
#include "engine/core/Scene.hpp"
#include "engine/resource/ResourceManager.hpp"
#include "EventsHandler.hpp"

namespace engine {

	class System;

	class Game {
	public:
		Game(bool enableVideo, std::string const& cwd);
		virtual ~Game();

		using SceneModel = std::function<void (Game&, Scene&)>;
		using SceneModels = std::unordered_map<std::string, SceneModel>;

		void play(std::string const& name);
		void replaceScene(std::string const& name);
		void pushScene(std::string const& name);
		void popScene();

		void registerSystem(std::string const& name, System* system);
		void registerSceneModel(std::string const& name, SceneModel const& sceneModel);

		irr::IrrlichtDevice* device();
		irr::IrrlichtDevice const* device() const;

		std::string const& getcwd() const;

	private:
		 Events _keyEvents;

	public:
		EventsHandler eventsHandler;

	private:
		irr::IrrlichtDevice* _device;
		EventsReceiver _eventReceiver;
		std::unordered_map<std::string, System*> _systems;
		std::list<Scene> _scenes;
		SceneModels _sceneModels;
		std::string _cwd;

		void _updateScenes();
	};
}
