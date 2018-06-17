/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Menu Main Cpp
*/
 
#include "engine/core/Game.hpp"
#include "engine/core/Scene.hpp"
#include "engine/systems/DisplaySystem.hpp"
#include "engine/systems/MenuEngineSystem.hpp"
 
#include "game/scenes/MainMenu.hh"
#include "game/scenes/PlayMenu.hh"
#include "game/scenes/WaitingMenu.hh"
#include "game/scenes/OptionsMenu.hh"
#include "game/scenes/KeyAssign.hh"
#include "game/scenes/CreditsMenu.hh"
 
namespace worms {
 
  void start() {
    engine::Game game(true, "./assets/");
    game.registerSystem("effects", new engine::Menu::MenuEngineSystem);
    game.registerSystem("display", new engine::DisplaySystem(game));
 
    game.registerSceneModel("mainMenu", worms::scene::mainMenu);
    game.registerSceneModel("playMenu", worms::scene::playScene);
    game.registerSceneModel("waintingMenu", worms::scene::waitingScene);
    game.registerSceneModel("optionsMenu", worms::scene::optionsScene);
    game.registerSceneModel("keyAssign", worms::scene::keyAssign);
    game.registerSceneModel("creditsMenu", worms::scene::creditsScene);
    game.play("mainMenu");
  }
}
 
int main()
{
  try {
    worms::start();
  } catch (std::exception& e) {
    std::cerr << "worms: ERROR: " << e.what() << std::endl;
    return 1;
  }
 
  return 0;
}