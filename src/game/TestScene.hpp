/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include "engine/core/Scene.hpp"

namespace testGame {

	class TestScene : public engine::Scene {
	public:
		TestScene();
		virtual ~TestScene();

		void update() override;

	private:
		engine::Entity const* _entity;
		engine::Entity const* _entity2;
	};
}
