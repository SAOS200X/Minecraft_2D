#include "pch.h"
#include "DropDownBox.h"

DropDownBox::DropDownBox(sf::Vector2f size, sf::Vector2f position, sf::Color color, const sf::Font* font, unsigned int characterSize, unsigned int maxRow)
{
	init();
	this->maxRow = maxRow;
	defaultColor = color;
	rectangle.setSize(size);

	boxs.push_back(properties("NONE", sf::FloatRect(position - (size / 2.f), size), color));

	if (font)
	{
		text.setFont(*font);
		text.setCharacterSize(characterSize);
	}
}

DropDownBox::DropDownBox(const sf::Texture* texture, sf::Vector2f position, const sf::Font* font, unsigned int characterSize, unsigned int maxRow)
{
	init();
	this->maxRow = maxRow;

	rectangle.setSize(static_cast<sf::Vector2f>(texture->getSize()));
	rectangle.setTexture(texture);

	boxs.push_back(properties("NONE", sf::FloatRect(position - (rectangle.getSize() / 2.f), (rectangle.getSize())), sf::Color::White));

	if (font)
	{
		text.setFont(*font);
		text.setCharacterSize(characterSize);
	}
}

DropDownBox::~DropDownBox()
{
}

void DropDownBox::update(sf::Vector2f mousePosWindow, bool isButtonPressed)
{
	for (unsigned int i = 0; i < boxs.size(); i++)
	{
		if (i > maxRow + scroll)
			break;
		else if (i && i <= scroll)
			continue;

		sf::FloatRect rect;

		if (!i)
			rect = boxs.at(i).rect;
		else
			rect = boxs.at(i - scroll).rect;

		if (rect.contains(mousePosWindow))
		{
			boxs.at(i).outlineColor = sf::Color::Red;
			if (isButtonPressed)
			{
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
			if (i == currentRow)
			{
				boxs.at(i).fillColor = defaultColor - sf::Color(50, 50, 50, 0);
				boxs.at(i).outlineColor = sf::Color::Red;
			}
			else {
				boxs.at(i).fillColor = defaultColor;
				boxs.at(i).outlineColor = sf::Color::Black;
			}
		}
	}
}

void DropDownBox::render(sf::RenderTarget* target)
{	
	for (UINT32 i = 0; i < boxs.size(); i++)
	{
		if (i > maxRow + scroll)
			break;
		else if (i && i <= scroll)
			continue;

		if (i)
			rectangle.setPosition(boxs.at(i - scroll).rect.getPosition());
		else
			rectangle.setPosition(boxs.at(i).rect.getPosition());

		rectangle.setFillColor(boxs.at(i).fillColor);
		rectangle.setOutlineColor(boxs.at(i).outlineColor);
		target->draw(rectangle);

		text.setString(boxs.at(i).name);
		text.setOrigin(text.getLocalBounds().getSize().x / 2.f, text.getCharacterSize() * 0.65f);
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
		currentRow = current + 1;
		boxs.front().name = boxs.at(currentRow).name;
	}
	else
		logWARNING("value not valid!!!");
}

void DropDownBox::scrollUp()
{
	if (show)
	{
		if (scroll > 0)
			scroll--;
	}
}

void DropDownBox::ScrollDown()
{
	if (show)
	{
		if (static_cast<size_t>(maxRow) + scroll < boxs.size() - 1)
			scroll++;
	}
}

const unsigned int DropDownBox::getCurrent()
{
	return (currentRow - 1);
}

void DropDownBox::init()
{
	show = false;
	currentRow = 0;
	this->maxRow = 0;
	scroll = 0;
	defaultColor = sf::Color::White;
	rectangle.setOutlineThickness(2.f);
	text.setOutlineThickness(2.f);
}
