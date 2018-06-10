/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** KeyFinder
*/

#include "KeyFinder.hpp"

engine::Menu::KeyFinder::KeyFinder()
{
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_LBUTTON, "LMouse"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_RBUTTON, "RMouse"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_CANCEL, "Cance"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_MBUTTON, "MMouse"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_BACK, "Back"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_TAB, "Tab"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_CLEAR, "Clear"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_RETURN, "Enter"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_SHIFT, "Shift"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_CONTROL, "Control"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_MENU, "Alt"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_PAUSE, "Pause"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_CAPITAL, "CapsLock"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_ESCAPE, "ESC"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_SPACE, "Space"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_PRIOR, "PageUp"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_NEXT, "PageDown"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_END, "End"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_HOME, "Home"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_LEFT, "Left"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_UP, "Up"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_RIGHT, "Right"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_DOWN, "Down"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_SELECT, "Select"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_PRINT, "Print"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_EXECUT, "Exec"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_SNAPSHOT, "PrintScreen"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_INSERT, "Insert"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_DELETE, "Delete"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_HELP, "Help"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_A, "A"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_B, "B"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_C, "C"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_D, "D"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_E, "E"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_F, "F"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_G, "G"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_H, "H"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_I, "I"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_J, "J"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_K, "K"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_L, "L"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_M, "M"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_N, "N"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_O, "O"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_P, "P"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_Q, "Q"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_R, "R"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_S, "S"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_T, "T"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_U, "U"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_V, "V"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_W, "W"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_X, "X"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_Y, "Y"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_Z, "Z"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_0, "0"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_1, "1"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_2, "2"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_3, "3"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_4, "4"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_5, "5"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_6, "6"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_7, "7"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_8, "8"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_KEY_9, "9"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_LWIN, "LWin"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_RWIN, "RWin"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_APPS, "Apps"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_SLEEP, "Sleep"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_NUMPAD0, "Num0"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_NUMPAD1, "Num1"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_NUMPAD2, "Num2"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_NUMPAD3, "Num3"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_NUMPAD4, "Num4"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_NUMPAD5, "Num5"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_NUMPAD6, "Num6"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_NUMPAD7, "Num7"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_NUMPAD8, "Num8"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_NUMPAD9, "Num9"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_MULTIPLY, "Multiply"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_ADD, "Add"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_SEPARATOR, "Seperator"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_SUBTRACT, "Sub"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_DECIMAL, "Deci"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_DIVIDE, "Div"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F1, "F1"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F2, "F2"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F3, "F3"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F4, "F4"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F5, "F5"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F6, "F6"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F7, "F7"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F8, "F8"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F9, "F9"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F10, "F10"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F11, "F11"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F12, "F12"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F13, "F13"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F14, "F14"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F15, "F15"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F16, "F16"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F17, "F17"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F18, "F18"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F19, "F19"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F20, "F20"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F21, "F21"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F22, "F22"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F23, "F23"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_F24, "F24"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_NUMLOCK, "NumLock"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_SCROLL, "ScrollLock"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_LSHIFT, "LShft"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_RSHIFT, "RShft"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_LCONTROL, "LCtrl"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_RCONTROL, "RCtrl"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_LMENU, "LAlt"));
	_keys.insert(std::pair<irr::EKEY_CODE, std::string>(irr::KEY_RMENU, "RAlt"));
}

std::string engine::Menu::KeyFinder::findKey(irr::EKEY_CODE key)
{
	for (std::pair<irr:: EKEY_CODE, std::string> keyElem : _keys) {
		if (keyElem.first == key) 
			return (keyElem.second);
	}
	return ("UNKOWN");
}