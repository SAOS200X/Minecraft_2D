#pragma once
class DropDownBox
{
public:
	DropDownBox(sf::Vector2f size, sf::Vector2f position, sf::Color color, const sf::Font* font = nullptr, unsigned int characterSize = 16, unsigned short max = 4);
	~DropDownBox();

	void update(sf::Vector2f mousePosWindow, const UINT32 dt);
	void render(sf::RenderTarget* target);

	void push(std::string str);
	void setCurrent(unsigned short current);

private:
	void init();


private:
	sf::RectangleShape rectangle;
	sf::Vector2f position;
	sf::Color color;
	sf::Sprite sprite;
	std::vector<std::string> vector;

	sf::Text text;

	unsigned short current;
	sf::Vector2f mousePosWindow;
	unsigned short max;

	bool show;
	UINT32 delay;
};

