#include "pch.h"
#include "s_System.h"

const sf::RenderWindow const* s_System::getWindow()
{
	return window;
}

const sf::Vector2i& s_System::getMousePosWindow()
{
	return mousePosWindow;
}

std::map<unsigned short, s_System::state> s_System::KeyState;
std::map<unsigned short, s_System::state> s_System::MouseState;

sf::RenderWindow const* s_System::window = nullptr;
sf::Font* s_System::font = nullptr;
sf::Vector2i s_System::mousePosWindow;
