#include "pch.h"
#include "gameSave.h"


gameSave::gameSave(const sf::Vector2f size, const sf::Vector2f position, const sf::Font* font, const std::string name, const std::string filePath)
{
    select = false;

    m_p.name = name;
    m_p.filePath = filePath;

    bound.setSize(size);
    bound.setOrigin(size / 2.f);
    bound.setPosition(position);
    bound.setFillColor(sf::Color::Transparent);
    bound.setOutlineColor(sf::Color::Transparent);
    bound.setOutlineThickness(3.f);


    text_1.setFont(*font);
    text_1.setCharacterSize(size.y / 3U);
    text_2 = text_1;
    text_1.setPosition(bound.getGlobalBounds().getPosition().x + size.y, bound.getGlobalBounds().getPosition().y);
    text_1.setString(name);


    text_2.setPosition(bound.getGlobalBounds().getPosition().x + size.y, bound.getGlobalBounds().getPosition().y + size.y / 2.f - text_2.getCharacterSize() * 0.35f);
    text_2.setFillColor(sf::Color(160, 160, 160));
    text_2.setString(filePath);
}

gameSave::~gameSave()
{
}

void gameSave::update(const sf::Vector2f mousePosWindow, const bool isButtonPressed)
{
    if (isButtonPressed)
        if (bound.getGlobalBounds().contains(mousePosWindow))
        {
            select = true;
            bound.setOutlineColor(sf::Color::White);
        }
        else
        {
            select = false;
            bound.setOutlineColor(sf::Color::Transparent);
        }
    else if (bound.getGlobalBounds().contains(mousePosWindow) || select)
        bound.setOutlineColor(sf::Color::White);
    else
        bound.setOutlineColor(sf::Color::Transparent);
}

void gameSave::render(sf::RenderTarget* target)
{
    target->draw(bound);
    target->draw(text_1);
    target->draw(text_2);
}
