#pragma once
class DropDownBox
{
public:
	DropDownBox(sf::Vector2f size, sf::Vector2f position, sf::Color color, const sf::Font* font = nullptr, unsigned int characterSize = 16, unsigned int max = 4);
	~DropDownBox();

	void update(sf::Vector2f mousePosWindow);
	void render(sf::RenderTarget* target);

	void push(const std::string& str);
	void push(const std::vector<std::string> str);
	void setCurrent(unsigned int current);
	const unsigned int& getCurrent();

private:
	sf::RectangleShape rectangle;
	sf::Vector2f position;
	sf::Color color;
	sf::Sprite sprite;
	std::vector<std::string> list;

	sf::Text text;

	unsigned int current;
	sf::Vector2f mousePosWindow;
	unsigned int max;

	bool show;
};

