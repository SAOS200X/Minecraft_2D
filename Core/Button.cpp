#include "pch.h"
#include "Button.h"

Button::Button(sf::Vector2u size, sf::Vector2f position, sf::Color color, const sf::Font* font, unsigned int characterSize, std::string str)
{
	active = false;

	//if (!this->texture->create(size.x, size.y))
		//logWARNING("couldn't create texture!");

	//sprite.setTexture(*texture);
	sprite.setSize(static_cast<sf::Vector2f>(size));
	sprite.setOrigin(size.x / 2.f, size.y / 2.f);
	sprite.setPosition(position);


	//sprite.setColor(color);
	sprite.setFillColor(color);
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

Button::Button(sf::Texture* texture, sf::Vector2f position, const sf::Font* font, unsigned int characterSize, std::string str)
{
	active = false;
	this->texture = texture;

	sprite.setSize(static_cast<sf::Vector2f>(texture->getSize()));
	sprite.setTexture(this->texture);
	sprite.setOrigin(this->texture->getSize().x / 2.f, this->texture->getSize().y / 2.f);
	sprite.setPosition(position);
	defaultColor = sf::Color::White;

	if (font)
	{
		text.setFont(*font);
		text.setCharacterSize(characterSize);
		text.setString(str);
		text.setOrigin(text.getGlobalBounds().getSize() / 2.f);
		text.setPosition(sprite.getPosition());
	}
}

Button::Button(const std::string filePath, sf::Vector2f position, const sf::Font* font, unsigned int characterSize, std::string str)
{
	active = false;
	texture = new sf::Texture;

	if (!texture->loadFromFile(filePath))
		logWARNING("couldn't open file: " + filePath);

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
		text.setOrigin(text.getGlobalBounds().getSize() / 2.f);
		text.setPosition(sprite.getPosition());
	}
}

Button::~Button()
{
	if (texture)
		delete texture;
}

void Button::update(sf::Vector2f mousePosWindow, bool isKeyPressed)
{
	active = false;

	if (sprite.getGlobalBounds().contains(mousePosWindow))
	{
		if (isKeyPressed)
		{
			sprite.setFillColor(defaultColor - sf::Color(100, 100, 0, 20));
			active = true;
		}
		else
			sprite.setFillColor(defaultColor - sf::Color(80, 80, 0, 0));

	}
	else
		sprite.setFillColor(defaultColor);

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

