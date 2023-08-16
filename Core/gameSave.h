#pragma once
class gameSave
{
private:
    struct propertite {
        std::string name;
        std::string filePath;
        std::string seed;
        time_t date;
    } m_p;

public:
    gameSave(const sf::Vector2f size, const sf::Vector2f position, const sf::Font* font);
    ~gameSave();

    void update(const sf::Vector2f mousePosWindow, const bool isButtonPressed);

    void render(sf::RenderTarget* target);

    void setPropertite(const std::string name, const std::string filePath, const std::string seed, const time_t date);
    
    inline const propertite& getSaves() { return m_p; }
    
    inline const bool isSelect() { return select; }

    bool operator==(const std::string right) {
        return (this->m_p.name == right);
    }
private:
    void setString();

    sf::RectangleShape bound;
    sf::Text text_1;
    sf::Text text_2;

    bool select;
};

