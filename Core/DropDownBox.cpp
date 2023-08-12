#include "pch.h"
#include "DropDownBox.h"

DropDownBox::DropDownBox(sf::Vector2f size, sf::Vector2f position, sf::Color color, const sf::Font* font, unsigned int characterSize, unsigned int maxRow)
{
	show = false;
	currentRow = 0;
	this->maxRow = maxRow;
	defaultColor = color;

	rectangle.setSize(size);
	rectangle.setOutlineThickness(2.f);

	boxs.push_back(properties("NONE", sf::FloatRect(position - (size / 2.f), size), color));

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
	defaultColor = sf::Color::White;

	rectangle.setSize(static_cast<sf::Vector2f>(texture->getSize()));
	rectangle.setTexture(texture);
	rectangle.setOutlineThickness(2.f);

	boxs.push_back(properties("NONE", sf::FloatRect(position - (rectangle.getSize() / 2.f), (rectangle.getSize())), sf::Color::White));

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
	for (unsigned int i = 0; i< boxs.size();i++)
		if (boxs.at(i).rect.contains(mousePosWindow))
		{
			boxs.at(i).outlineColor = sf::Color::Red;
			if (isButtonPressed)
			{
				boxs.at(i).fillColor = defaultColor - sf::Color(80, 80, 0, 20);
				show = !show;
				if (i && (i != currentRow))
				{
					currentRow = i;
					boxs.front().name = boxs.at(i).name;
				}
			}
			else
				boxs.at(i).fillColor = defaultColor - sf::Color(50, 50, 0, 0);
		}
		else
		{
			boxs.at(i).fillColor = defaultColor;
			boxs.at(i).outlineColor = sf::Color::Black;
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
		text.setPosition(rectangle.getPosition() + rectangle.getSize() / 2.f);
		target->draw(text);

		if (!i && !show)
			break;
	}
}

void DropDownBox::push(const std::string& str)
{
	sf::FloatRect rect = boxs.back().rect;
	rect.top += boxs.back().rect.getSize().y + rectangle.getOutlineThickness() * 2.f;
	boxs.push_back(properties(str, rect, (rectangle.getTexture() ? sf::Color::White : boxs.back().fillColor)));
}

void DropDownBox::setCurrent(unsigned int current)
{
	if (current < boxs.size())
	{
		this->currentRow = current + 1;
		boxs.front().name = boxs.at(current + 1).name;
	}
	else
		logWARNING("value not valid!!!");
}

const unsigned int& DropDownBox::getCurrent()
{
	return (currentRow - 1);
}
