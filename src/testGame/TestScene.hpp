/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include "../engine/Scene.hpp"

namespace testGame {

	class TestScene : public engine::Scene {
	public:
		virtual ~TestScene();

		void update() override;
	};
}
