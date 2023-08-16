#include "pch.h"
#include "TextBox.h"

TextBox::TextBox(const sf::Vector2f size, const sf::Vector2f position, const sf::Color color, const sf::Font* font, const unsigned int characterSize)
{
	select = false;
	sprite.setSize(size);
	sprite.setFillColor(color);
	sprite.setOrigin(size / 2.f);
	sprite.setPosition(position);

	sprite.setOutlineThickness(3.f);
	sprite.setOutlineColor(sf::Color::Black);

	text.setFont(*font);
	text.setCharacterSize(characterSize);
	text.setOrigin(0.f, characterSize * 0.65f);
	text.setPosition(sprite.getGlobalBounds().getPosition().x + 10.f, position.y);
}

TextBox::TextBox(const sf::Texture* texture, const sf::Vector2f position, const sf::Font* font, const unsigned int characterSize)
{
	select = false;
	sprite.setTexture(texture);
	sprite.setSize(sprite.getSize());
	sprite.setOrigin(sprite.getSize() / 2.f);
	sprite.setPosition(position);

	sprite.setOutlineThickness(3.f);
	sprite.setOutlineColor(sf::Color::Black);

	text.setFont(*font);
	text.setCharacterSize(characterSize);
	text.setOrigin(0.f, characterSize * 0.65f);
	text.setPosition(sprite.getGlobalBounds().getPosition().x + 10.f, position.y);
}

TextBox::~TextBox()
{
}

void TextBox::update(const sf::Vector2f mousePosWindow, const bool isButtonPressed)
{
	if (isButtonPressed)
		if (sprite.getGlobalBounds().contains(mousePosWindow))
		{
			select = true;
			sprite.setOutlineColor(sf::Color::White);
		}
		else
		{
			select = false;
			sprite.setOutlineColor(sf::Color::Black);

		}
}

void TextBox::render(sf::RenderTarget* target)
{
	target->draw(sprite);
	target->draw(text);
}

void TextBox::typed(const unsigned int utf)
{
	if (select)
	{
		if (utf == 8)
		{
			if (str.size() > 0)
			{
				str.erase(str.end() - 1);
				text.setString(str);
			}
		}
		else if (utf >= 32)
		{
			str += static_cast<char>(utf);
			text.setString(str);
		}
	}
}

