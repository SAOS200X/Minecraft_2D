#include "pch.h"
#include "Button.h"

Button::Button(const sf::Vector2u size, const sf::Vector2f position, const sf::Color color, const sf::Font* font, unsigned int characterSize, std::string str)
{
	active = true;
	pressed = false;

	sprite.setSize(static_cast<sf::Vector2f>(size));
	sprite.setOrigin(size.x / 2.f, size.y / 2.f);
	sprite.setPosition(position);


	sprite.setFillColor(color);
	defaultColor = color;

	if (font)
	{
		text.setFont(*font);
		text.setCharacterSize(characterSize);
		text.setString(str);
		text.setOrigin(text.getLocalBounds().getSize().x / 2.f, characterSize * 0.65f);

		text.setPosition(sprite.getPosition());
	}
}

Button::Button(const sf::Texture* texture, const sf::Vector2f position, const sf::Font* font, unsigned int characterSize, std::string str)
{
	active = true;
	pressed = false;

	sprite.setSize(static_cast<sf::Vector2f>(texture->getSize()));
	sprite.setTexture(texture);
	sprite.setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
	sprite.setPosition(position);
	defaultColor = sf::Color::White;

	if (font)
	{
		text.setFont(*font);
		text.setCharacterSize(characterSize);
		text.setString(str);
		text.setOrigin(text.getLocalBounds().getSize().x / 2.f, characterSize * 0.65f);

		text.setPosition(sprite.getPosition());
	}

}

Button::~Button()
{

}

void Button::update(const sf::Vector2f mousePosWindow, const bool isButtonPressed)
{
	if (active)
	{
		pressed = false;

		if (sprite.getGlobalBounds().contains(mousePosWindow))
		{
			if (isButtonPressed)
			{
				sprite.setFillColor(defaultColor - sf::Color(100, 100, 0, 20));
				pressed = true;
			}
			else
				sprite.setFillColor(defaultColor - sf::Color(80, 80, 0, 0));

		}
		else
			sprite.setFillColor(defaultColor);
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(sprite);
	if (text.getFont())
		target->draw(text);
}

void Button::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

void Button::setActive(const bool state)
{
	active = state;
	if (active)
	{
		sprite.setFillColor(defaultColor);
		text.setFillColor(sf::Color::White);
	}
	else
	{
		sprite.setFillColor(defaultColor - sf::Color(100,100,100,80));
		text.setFillColor(sf::Color(200,200,200,200));
	}
}

