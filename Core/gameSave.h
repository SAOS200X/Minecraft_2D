#pragma once
class gameSave
{
private:
    struct propertite {
        std::string name;
        std::string filePath;
    } m_p;

public:
    gameSave(const sf::Vector2f size, const sf::Vector2f position, const sf::Font* font, const std::string name, const std::string filePath);
    ~gameSave();

    void update(const sf::Vector2f mousePosWindow, const bool isButtonPressed);

    void render(sf::RenderTarget* target);

    
    inline const propertite& getSaves() { return m_p; }
    
    inline const bool isSelect() { return select; }

private:
    

    sf::RectangleShape bound;
    sf::Text text_1;
    sf::Text text_2;

    bool select;
};

