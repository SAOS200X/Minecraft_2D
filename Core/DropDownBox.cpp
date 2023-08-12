#include "pch.h"
#include "DropDownBox.h"

DropDownBox::DropDownBox(sf::Vector2f size, sf::Vector2f position, sf::Color color, const sf::Font* font, unsigned int characterSize, unsigned int maxRow)
{
	show = false;
	currentRow = 0;
	this->maxRow = maxRow;

	rectangle.setSize(size);
	rectangle.setOrigin(size / 2.f);
	rectangle.setOutlineThickness(2.f);

	boxs.push_back(properties("NONE", sf::FloatRect(position, size), sf::Color::White));

	if (font)
	{
		text.setFont(*font);
		text.setCharacterSize(characterSize);
		text.setOutlineThickness(2.f);
	}
}

DropDownBox::DropDownBox(sf::Texture* texture, sf::Vector2f position, const sf::Font* font, unsigned int characterSize, unsigned int maxRow)
{
	show = false;
	currentRow = 0;
	this->maxRow = maxRow;

	rectangle.setSize(static_cast<sf::Vector2f>(texture->getSize()));
	rectangle.setTexture(texture);
	rectangle.setOrigin(rectangle.getSize() / 2.f);
	rectangle.setOutlineThickness(2.f);

	boxs.push_back(properties("NONE", sf::FloatRect(position, rectangle.getSize()), sf::Color::White));

	if (font)
	{
		text.setFont(*font);
		text.setCharacterSize(characterSize);
		text.setOutlineThickness(2.f);
	}
}

DropDownBox::~DropDownBox()
{
}

void DropDownBox::update(sf::Vector2f mousePosWindow, bool isButtonPressed)
{
	for (auto& i : boxs)
		if (i.rect.contains(mousePosWindow))
		{
			i.outlineColor = sf::Color::Red;
			if (isButtonPressed)
			{
				i.fillColor = boxs.front().fillColor - sf::Color(80, 80, 0, 20);
				show = !show;
			}
			else
				i.fillColor = boxs.front().fillColor - sf::Color(50, 50, 0, 0);
		}
		else
		{
			i.fillColor = boxs.front().fillColor;
			i.outlineColor = sf::Color::Black;
		}
}

void DropDownBox::render(sf::RenderTarget* target)
{	
	for (UINT32 i = 0; i < (maxRow >= boxs.size() ? boxs.size() : maxRow); i++)
	{
		rectangle.setPosition(boxs.at(i).rect.getPosition());
		rectangle.setFillColor(boxs.at(i).fillColor);
		rectangle.setOutlineColor(boxs.at(i).outlineColor);
		target->draw(rectangle);

		text.setString(boxs.at(i).name);
		text.setOrigin(text.getGlobalBounds().getSize() / 2.f);
		text.setPosition(rectangle.getPosition());
		target->draw(text);

		if (!i && !show)
			break;
	}
}

void DropDownBox::push(const std::string& str)
{
	sf::FloatRect rect = boxs.back().rect;
	rect.top += boxs.back().rect.getSize().y + rectangle.getOutlineThickness();
	boxs.push_back(properties(str, rect, (rectangle.getTexture() ? sf::Color::White : boxs.back().fillColor)));
}

void DropDownBox::setCurrent(unsigned int current)
{
	if (current < boxs.size())
		this->currentRow = current;
	else
		logWARNING("value not valid!!!");
}

const unsigned int& DropDownBox::getCurrent()
{
	return currentRow;
}
