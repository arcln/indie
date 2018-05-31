/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** My Script Parser Cpp
*/

#include "MyScriptParser.hpp"

engine::Menu::MyScriptParser::MyScriptParser(std::string path, engine::Scene *scene, engine::Game *game)
{
	_path = path;
	_elementHandled.insert(std::pair<std::string, std::function<void(void)>>("button", [this](void) {manageButton();}));
	_game = game;
	_scene = scene;
	_isOver = false;
	parseFile();
	fillMap();
}

void engine::Menu::MyScriptParser::parseFile()
{
	std::ifstream file(_path.c_str(), std::ios::in);
	std::vector<std::string> tmp;
	std::string buffer;

	if (!file.is_open())
		std::cerr << "Can't open " << _path << std::endl;
	while (std::getline(file, buffer))
		tmp.push_back(buffer);
	_storage = tmp;
}

int engine::Menu::MyScriptParser::checkStart(std::string line, std::string chars)
{
	for (std::size_t i = 0; i < chars.size(); i = i + 1) {
		if (chars[i] == line[0]) {
			return (1);
		}
	}
	return (0);
}

int engine::Menu::MyScriptParser::checkElement(std::string elementName, int line)
{
	int check = 0;

	for (std::pair<std::string, std::function<void(void)>> elem : _elementHandled) {
		if (elem.first == elementName)
			check = 1;
	}
	if (check == 0) {
		std::cerr << "Unknow element type at line " << line << " : [" << elementName << "]." << std::endl;
	}
	return (check);
}

void engine::Menu::MyScriptParser::fillMap()
{
	std::vector<std::string> tmp;
	std::string line;
	std::string type;

	_lineNb = 0;
	for (_it = _storage.begin(); _it != _storage.end() && _isOver == false; ++_it) {
		_lineNb += 1;
		line = *_it;
		if (line.empty() == true)
			continue;
		if (checkStart(line, "\t") == 0) {
			type = line.substr(0, line.find(":"));
			if (checkElement(type, _lineNb) == 1) {
				std::cout << type << " : OK." << std::endl;
				createElement(type);
			}
		}
	}
}

void engine::Menu::MyScriptParser::createElement(std::string type)
{
	for (std::pair<std::string, std::function<void(void)>> elem : _elementHandled) {
		if (elem.first == type) {
			elem.second();
			break;
		}
	}
}

void engine::Menu::MyScriptParser::manageButton()
{
	std::string line;
	std::string command;
	std::string param;
	EntityId currentEntity = _scene->spawnEntity("button");
	ComponentFilter<engine::ButtonComponent, engine::IrrlichtComponent> filter;
	ComponentFilter<engine::ButtonComponent, engine::IrrlichtComponent>::Callback callback;
	engine::ButtonComponent button;
	irr::gui::IGUIButton *irrButton;
	
	filter.get(currentEntity, [](auto& buttonComponent, auto& irrlichtComponent) {
		callback(buttonComponent);
		irrlichtComponent.node;
	});
	std::cout << "\nDEBUG\n" << std::endl;
	_it += 1;
	engine::Menu::ButtonFactory factory(irrButton);
	for (; _it != _storage.end() ; ++_it) {
		line = *_it;
		_lineNb += 1;
		if (checkStart(line, "\t") == 0)
			break;
		command = line.substr(line.find('-', 1) + 2, line.find(':', 1) - (line.find('-', 1) + 2));
		param = line.substr(line.find(':', 1) + 2, line.size() - (line.find(':') + 2));
		std::cout << "Command : [" << command << "]. | Param : [" << param << "]." << std::endl;
		for (std::pair<std::string, std::function<void(std::string)>> commandHandl : factory._handledFunc ) {
			if (commandHandl.first == command) {
				commandHandl.second(param);
			}
		}
	}
	if (_it == _storage.end())
		_isOver = true;
}