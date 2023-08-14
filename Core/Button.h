#pragma once
class Button
{
public:
	Button(const sf::Vector2u size, const sf::Vector2f position, const sf::Color color, const sf::Font* font = nullptr, unsigned int characterSize = 0, std::string str = "");
	Button(const sf::Texture* texture, const sf::Vector2f position, const sf::Font* font = nullptr, unsigned int characterSize = 0, std::string str = "");


	~Button();

	void update(const sf::Vector2f mousePosWindow, const bool isButtonPressed);
	void render(sf::RenderTarget* target);

	void setPosition(sf::Vector2f position);

	void setActive(const bool state);

	inline const bool isButtonPressed() const { return pressed; }

private:
	sf::RectangleShape sprite;

	sf::Color defaultColor;

	sf::Text text;

	bool pressed;

	bool active;
};

