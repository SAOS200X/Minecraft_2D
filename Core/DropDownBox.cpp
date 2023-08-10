#include "pch.h"
#include "DropDownBox.h"

DropDownBox::DropDownBox(sf::Vector2f size, sf::Vector2f position, sf::Color color, const sf::Font* font, unsigned int characterSize, unsigned int max)
{
	this->position = position;
	this->color = color;
	this->max = max;
	current = 0;
	show = false;

	rectangle.setSize(size);
	rectangle.setOrigin(size / 2.f);
	rectangle.setPosition(position);
	rectangle.setOutlineThickness(2.f);

	if (font)
		text.setFont(*font);
	text.setCharacterSize(characterSize);
	text.setOutlineThickness(2.f);
}

DropDownBox::~DropDownBox()
{
}

void DropDownBox::update(sf::Vector2f mousePosWindow)
{
	rectangle.setPosition(position);
	rectangle.setOutlineColor(sf::Color::Black);
	this->mousePosWindow = mousePosWindow;

	if (rectangle.getGlobalBounds().contains(mousePosWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			rectangle.setFillColor(color - sf::Color(80, 80, 0, 20));
			show = !show;
		}
		else
			rectangle.setFillColor(color - sf::Color(50, 50, 0, 0));
	}
	else
		rectangle.setFillColor(color);
}

void DropDownBox::render(sf::RenderTarget* target)
{
	target->draw(rectangle);
	if ((list.size() > 0) && (current < list.size()))
	{
		text.setString(list.at(current));

		text.setOrigin(text.getGlobalBounds().getSize() / 2.f);
		text.setPosition(rectangle.getPosition());
		target->draw(text);
	}

	if (show)
		for (UINT32 i = 0; i < (max >= list.size() ? list.size() : max); i++)
		{
			rectangle.setPosition(position.x, position.y + (rectangle.getSize().y + 4.f) * (i + 1));

			if (rectangle.getGlobalBounds().contains(mousePosWindow))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					rectangle.setFillColor(color - sf::Color(80, 80, 0, 20));
					show = !show;
					current = i;
				}
				else
					rectangle.setFillColor(color - sf::Color(50, 50, 0, 0));
			}
			else
				rectangle.setFillColor(color + sf::Color(50, 50, 50, 0));
			if (i == current)
			{
				rectangle.setFillColor(color - sf::Color(20, 20, 0, 0));
				rectangle.setOutlineColor(sf::Color::Red);
			}
			else 
				rectangle.setOutlineColor(sf::Color::Black);


			target->draw(rectangle);

			if ((list.size() > 0) && (i <= list.size()))
			{
				text.setString(list.at(i));
				text.setOrigin(text.getGlobalBounds().getSize() / 2.f);
				text.setPosition(rectangle.getPosition());
				target->draw(text);
			}
		}
}

void DropDownBox::push(const std::string& str)
{
	list.push_back(str);
}

void DropDownBox::push(const std::vector<std::string> str)
{
	list = str;
}

void DropDownBox::setCurrent(unsigned int current)
{
	if (current <= max)
		this->current = current;
	else
		logERROR("value not valid!!!");
}

const unsigned int& DropDownBox::getCurrent()
{
	return current;
}
