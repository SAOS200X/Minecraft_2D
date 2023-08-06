#include "pch.h"
#include "Button.h"

Button::Button(sf::Vector2u size, sf::Vector2f position, sf::Color color, const sf::Font* font, unsigned int characterSize, std::string str)
{
	active = false;
	this->font = font;
	this->texture = new sf::Texture;

	if (!this->texture->create(size.x, size.y))
		logWARNING("couldn't create texture!");

	sprite.setTexture(*texture);
	sprite.setOrigin(size.x / 2.f, size.y / 2.f);
	sprite.setPosition(position);
	sprite.setColor(color);
	defaultColor = color;

	if (font)
	{
		text.setFont(*font);
		text.setCharacterSize(characterSize);
		text.setString(str);
		text.setOrigin(text.getGlobalBounds().getSize() / 2.f);
		text.setPosition(sprite.getPosition());
	}
}

Button::Button(sf::Texture* texture, sf::Vector2f position)
{
	active = false;
	font = nullptr;
	this->texture = nullptr;

	sprite.setTexture(*texture);
	sprite.setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
	sprite.setPosition(position);
	defaultColor = sf::Color::White;
}

Button::Button(std::string filePath, sf::Vector2f position)
{
	active = false;
	font = nullptr;
	this->texture = new sf::Texture;

	if (!this->texture->loadFromFile(filePath))
		logWARNING("couldn't open file: " + filePath);

	sprite.setTexture(*texture);
	sprite.setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
	sprite.setPosition(position);
	defaultColor = sf::Color::White;
}

Button::~Button()
{
	if (texture)
		delete texture;
}

void Button::update(sf::Vector2f mousePosWindow)
{
	active = false;

	if (sprite.getGlobalBounds().contains(mousePosWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sprite.setColor(defaultColor - sf::Color(100, 100, 0, 20));
			active = true;
		}
		else
			sprite.setColor(defaultColor - sf::Color(80, 80, 0, 0));

	}
	else
		sprite.setColor(defaultColor);

}

void Button::render(sf::RenderTarget* target)
{
	target->draw(sprite);

	if (font)
		target->draw(text);
}

void Button::initButton()
{
}
