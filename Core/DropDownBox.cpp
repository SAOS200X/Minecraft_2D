#include "pch.h"
#include "DropDownBox.h"

DropDownBox::DropDownBox(sf::Vector2f size, sf::Vector2f position, sf::Color color, const sf::Font* font, unsigned int characterSize, unsigned short max)
{
	this->position = position;
	this->color = color;
	this->max = max;
	current = 0;
	show = false;
	delay = 0;

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

void DropDownBox::update(sf::Vector2f mousePosWindow, const UINT32 dt)
{
	delay += dt;
	rectangle.setPosition(position);
	rectangle.setOutlineColor(sf::Color::Black);
	this->mousePosWindow = mousePosWindow;

	if (rectangle.getGlobalBounds().contains(mousePosWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (delay > 100))
		{
			rectangle.setFillColor(color - sf::Color(80, 80, 0, 20));
			show = !show;
			delay = 0;
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
	if ((vector.size() > 0) && (current < vector.size()))
	{
		text.setString(vector.at(current));

		text.setOrigin(text.getGlobalBounds().getSize() / 2.f);
		text.setPosition(rectangle.getPosition());
		target->draw(text);
	}

	if (show)
		for (UINT32 i = 0; i < (max >= vector.size() ? vector.size() : max); i++)
		{
			rectangle.setPosition(position.x, position.y + (rectangle.getSize().y + 4.f) * (i + 1));

			if (rectangle.getGlobalBounds().contains(mousePosWindow))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (delay > 100))
				{
					rectangle.setFillColor(color - sf::Color(80, 80, 0, 20));
					show = !show;
					current = i;
					delay = 0;
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

			if ((vector.size() > 0) && (i <= vector.size()))
			{
				text.setString(vector.at(i));
				text.setOrigin(text.getGlobalBounds().getSize() / 2.f);
				text.setPosition(rectangle.getPosition());
				target->draw(text);
			}
		}
}

void DropDownBox::push(std::string str)
{
	vector.push_back(str);
}

void DropDownBox::setCurrent(UINT16 current)
{
	if (current <= max)
		this->current = current;
	else
		logERROR("value not valid!!!");
}

void DropDownBox::init()
{
	text.setFont(*s_System::getFont());
}
