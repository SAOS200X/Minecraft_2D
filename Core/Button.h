#pragma once
class Button
{
public:
	Button(sf::Vector2u size, sf::Vector2f position, sf::Color color, const sf::Font* font = nullptr, unsigned int characterSize = 0, std::string str = "");
	Button(sf::Texture* texture, sf::Vector2f position, const sf::Font* font = nullptr, unsigned int characterSize = 0, std::string str = "");
	Button(const std::string filePath, sf::Vector2f position, const sf::Font* font = nullptr, unsigned int characterSize = 0, std::string str = "");


	~Button();

	void update(sf::Vector2f mousePosWindow, bool isKeyPressed);
	void render(sf::RenderTarget* target);

	void setPosition(sf::Vector2f position);

	inline const bool isActive() const { return active; };

private:
	sf::Texture* texture = nullptr;

	//sf::Sprite sprite;
	sf::RectangleShape sprite;

	sf::Color defaultColor;

	sf::Text text;

	bool active;
};

