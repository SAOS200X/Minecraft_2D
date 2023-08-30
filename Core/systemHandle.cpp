#include "pch.h"
#include "systemHandle.h"


const sf::Texture* systemHandle::getTexture(const std::string filePath)
{
	return textures[filePath];
}

const sf::RenderWindow* const systemHandle::getWindow()
{
	return window;
}

sf::View* const systemHandle::getView()
{
	return view;
}

const sf::Vector2i& systemHandle::getMousePosWindow()
{
	return mousePosWindow;
}

const sf::Vector2f& systemHandle::getMousePosView()
{
	return mousePosView;
}

const sf::Font* const systemHandle::getFont(const unsigned int index)
{
	if (index < fonts.size())
		return fonts[index];
	else
		return nullptr;
}

const size_t& systemHandle::getDeltaTime()
{
	return *dt;
}

const bool systemHandle::isButtonPressed(const sf::Mouse::Button button)
{
	return (MouseState[button] == state::pressed);
}

const bool systemHandle::isKeyPressed(const sf::Keyboard::Key key)
{
	return (KeyState[key] == state::pressed);
}

const unsigned int systemHandle::getUTFCode()
{
	return utf;
}

void systemHandle::loadTexture(const std::string filePath)
{
	if (!textures.count(filePath))
	{
		textures.insert({ filePath, new sf::Texture });
		if (!textures.at(filePath)->loadFromFile(filePath))
			logWARNING("couldn't load image: " + filePath);
	}

}

void systemHandle::loadFont(const std::string filePath)
{
	fonts.push_back(new sf::Font);
	if (!fonts.back()->loadFromFile(filePath))
		logWARNING("couldn't load font: " + filePath);
}

std::map<std::string, sf::Texture*> systemHandle::textures;
std::vector<sf::Font*> systemHandle::fonts;
std::map<sf::Keyboard::Key, systemHandle::state> systemHandle::KeyState;
std::map<sf::Mouse::Button, systemHandle::state> systemHandle::MouseState;

const sf::RenderWindow* systemHandle::window = nullptr;
sf::View* systemHandle::view = nullptr;
sf::Vector2i systemHandle::mousePosWindow;
sf::Vector2f systemHandle::mousePosView;
size_t* systemHandle::dt;
unsigned int systemHandle::utf;
