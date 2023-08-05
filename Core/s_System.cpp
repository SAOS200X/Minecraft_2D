#include "pch.h"
#include "s_System.h"

const sf::RenderWindow* const s_System::getWindow()
{
	return window;
}

const sf::Vector2i& s_System::getMousePosWindow()
{
	return mousePosWindow;
}

const sf::Font* const s_System::getFont()
{
	return font;
}

const INT32* const s_System::getDeltaTime()
{
	return dt;
}

std::map<unsigned short, s_System::state> s_System::KeyState;
std::map<unsigned short, s_System::state> s_System::MouseState;

const sf::RenderWindow* s_System::window = nullptr;
sf::Font* s_System::font = nullptr;
sf::Vector2i s_System::mousePosWindow;
INT32* s_System::dt;
