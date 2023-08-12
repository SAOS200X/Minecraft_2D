#include "pch.h"
#include "systemHandle.h"

const sf::RenderWindow* const systemHandle::getWindow()
{
	return window;
}

const sf::Vector2i& systemHandle::getMousePosWindow()
{
	return mousePosWindow;
}

const sf::Font* const systemHandle::getFont()
{
	return font;
}

const INT32* const systemHandle::getDeltaTime()
{
	return dt;
}

const bool systemHandle::isButtonPressed(const sf::Mouse::Button button)
{
	return (MouseState[button] == state::pressed);
}

std::map<sf::Keyboard::Key, systemHandle::state> systemHandle::KeyState;
std::map<sf::Mouse::Button, systemHandle::state> systemHandle::MouseState;

const sf::RenderWindow* systemHandle::window = nullptr;
sf::Font* systemHandle::font = nullptr;
sf::Vector2i systemHandle::mousePosWindow;
INT32* systemHandle::dt;
