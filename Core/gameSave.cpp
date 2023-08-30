#include "pch.h"
#include "gameSave.h"


gameSave::gameSave(const sf::Vector2f size, const sf::Vector2f position, const sf::Font* font)
{
    select = false;

    bound.setSize(size);
    bound.setOrigin(size / 2.f);
    bound.setPosition(position);
    bound.setFillColor(sf::Color::Transparent);
    bound.setOutlineColor(sf::Color::Transparent);
    bound.setOutlineThickness(3.f);


    text_1.setFont(*font);
    text_1.setCharacterSize(static_cast<unsigned int>(size.y / 3.f));
    text_2 = text_1;
    text_1.setPosition(bound.getGlobalBounds().getPosition().x + size.y, bound.getGlobalBounds().getPosition().y - text_1.getCharacterSize() * 0.15f);

    text_2.setLineSpacing(0.8f);
    text_2.setPosition(bound.getGlobalBounds().getPosition().x + size.y, bound.getGlobalBounds().getPosition().y + size.y / 2.f - text_2.getCharacterSize() * 0.5f);
    text_2.setFillColor(sf::Color(160, 160, 160));
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

void gameSave::setPropertite(const std::string& name, const std::string& filePath, const std::string& seed, const time_t& date)
{
    m_p.name = name;
    m_p.filePath = filePath;
    m_p.seed = seed;
    m_p.date = date;

    setString();
}

void gameSave::setString()
{
    text_1.setString(m_p.name);

    tm date;
    localtime_s(&date, &m_p.date);
    std::stringstream ss;

    ss << m_p.name << " (" << date.tm_mday << "/" << (date.tm_mon + 1) << "/" << (date.tm_year - 100) << " " << date.tm_hour << ":" << date.tm_min << ")\n"
        << "Seed: " << m_p.seed;
    text_2.setString(ss.str());
}
