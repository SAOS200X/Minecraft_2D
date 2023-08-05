#pragma once
class Button
{
public:
	Button(sf::Vector2u size, sf::Vector2f position, sf::Color color, sf::Font* font = nullptr, unsigned int characterSize = 0, std::string str = "");
	Button(sf::Texture* texture, sf::Vector2f position);
	Button(std::string filePath, sf::Vector2f position);


	~Button();

	void update(sf::Vector2f mousePosWindow);
	void render(sf::RenderTarget* target);

	inline const bool isActive() const { return active; };

private:
	void initButton();

private:
	sf::Texture* texture;
	sf::Sprite sprite;
	sf::Color defaultColor;

	sf::Font* font;
	sf::Text text;

	bool active;
};

