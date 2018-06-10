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
	_elementHandled.insert(std::pair<std::string, std::function<void(void)>>("image", [this](void) {manageImage();}));
	_elementHandled.insert(std::pair<std::string, std::function<void(void)>>("text", [this](void) {manageText();}));
	_elementHandled.insert(std::pair<std::string, std::function<void(void)>>("editBox", [this](void) {manageEditBox();}));
	_elementHandled.insert(std::pair<std::string, std::function<void(void)>>("checkBox", [this](void) {manageCheckBox();}));
	_game = game;
	_scene = scene;
	_isOver = false;
}

void engine::Menu::MyScriptParser::parseFile()
{
	_storage = ResourceManager<std::vector<std::string>>::instance().get(_path);
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
			if (checkElement(type, _lineNb) == 1)
				createElement(type);
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
	Entity entity = _scene->spawnEntity("button");
	engine::ButtonComponent buttoCompo = entity.get<engine::ButtonComponent>();
	std::string line;
	std::string command;
	std::string param;

	_it += 1;
	engine::Menu::ButtonFactory factory(buttoCompo.node, _game);
	buttoCompo._scene = _scene;
	for (; _it != _storage.end() ; ++_it) {
		line = *_it;
		_lineNb += 1;
		if (checkStart(line, "\t") == 0)
			break;
		command = line.substr(line.find('-', 1) + 2, line.find(':', 1) - (line.find('-', 1) + 2));
		param = line.substr(line.find(':', 1) + 2, line.size() - (line.find(':') + 2));
		for (std::pair<std::string, std::function<void(std::string)>> commandHandl : factory._handledFunc ) {
			if (commandHandl.first == command) {
				commandHandl.second(param);
			}
		}
	}
	if (_it == _storage.end())
		_isOver = true;
}

void engine::Menu::MyScriptParser::manageImage()
{
	Entity entity = _scene->spawnEntity("image");
	engine::ImageComponent imgCompo = entity.get<engine::ImageComponent>();
	std::string line;
	std::string command;
	std::string param;

	_it += 1;
	engine::Menu::ImageFactory factory(imgCompo.node, _game);
	for (; _it != _storage.end() ; ++_it) {
		line = *_it;
		_lineNb += 1;
		if (checkStart(line, "\t") == 0)
			break;
		command = line.substr(line.find('-', 1) + 2, line.find(':', 1) - (line.find('-', 1) + 2));
		param = line.substr(line.find(':', 1) + 2, line.size() - (line.find(':') + 2));
		for (std::pair<std::string, std::function<void(std::string)>> commandHandl : factory._handledFunc ) {
			if (commandHandl.first == command)
				commandHandl.second(param);
		}
	}
	if (_it == _storage.end())
		_isOver = true;
}

void engine::Menu::MyScriptParser::manageText()
{
	Entity entity = _scene->spawnEntity("staticText");
	engine::TextComponent textCompo = entity.get<engine::TextComponent>();
	std::string line;
	std::string command;
	std::string param;

	_it += 1;
	engine::Menu::TextFactory factory(textCompo.node, _game);
	for (; _it != _storage.end() ; ++_it) {
		line = *_it;
		_lineNb += 1;
		if (checkStart(line, "\t") == 0)
			break;
		command = line.substr(line.find('-', 1) + 2, line.find(':', 1) - (line.find('-', 1) + 2));
		param = line.substr(line.find(':', 1) + 2, line.size() - (line.find(':') + 2));
		for (std::pair<std::string, std::function<void(std::string)>> commandHandl : factory._handledFunc ) {
			if (commandHandl.first == command)
				commandHandl.second(param);
		}
	}
	if (_it == _storage.end())
		_isOver = true;
}

void engine::Menu::MyScriptParser::manageEditBox()
{
	Entity entity = _scene->spawnEntity("editBox");
	engine::EditBoxComponent editBoxCompo = entity.get<engine::EditBoxComponent>();
	std::string line;
	std::string command;
	std::string param;

	_it += 1;
	engine::Menu::EditBoxFactory factory(editBoxCompo.node, _game);
	for (; _it != _storage.end() ; ++_it) {
		line = *_it;
		_lineNb += 1;
		if (checkStart(line, "\t") == 0)
			break;
		command = line.substr(line.find('-', 1) + 2, line.find(':', 1) - (line.find('-', 1) + 2));
		param = line.substr(line.find(':', 1) + 2, line.size() - (line.find(':') + 2));
		for (std::pair<std::string, std::function<void(std::string)>> commandHandl : factory._handledFunc ) {
			if (commandHandl.first == command)
				commandHandl.second(param);
		}
	}
	if (_it == _storage.end())
		_isOver = true;
}

void engine::Menu::MyScriptParser::manageCheckBox()
{
	Entity entity = _scene->spawnEntity("checkBox");
	engine::CheckBoxComponent checkBoxCompo = entity.get<engine::CheckBoxComponent>();
	std::string line;
	std::string command;
	std::string param;

	_it += 1;
	engine::Menu::CheckBoxFactory factory(checkBoxCompo.node, _game);
	for (; _it != _storage.end() ; ++_it) {
		line = *_it;
		_lineNb += 1;
		if (checkStart(line, "\t") == 0)
			break;
		command = line.substr(line.find('-', 1) + 2, line.find(':', 1) - (line.find('-', 1) + 2));
		param = line.substr(line.find(':', 1) + 2, line.size() - (line.find(':') + 2));
		for (std::pair<std::string, std::function<void(std::string)>> commandHandl : factory._handledFunc ) {
			if (commandHandl.first == command)
				commandHandl.second(param);
		}
	}
	if (_it == _storage.end())
		_isOver = true;
}
