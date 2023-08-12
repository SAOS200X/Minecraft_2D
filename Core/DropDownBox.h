#pragma once
class DropDownBox
{
public:
	DropDownBox(sf::Vector2f size, sf::Vector2f position, sf::Color defaultColor, const sf::Font* font = nullptr, unsigned int characterSize = 16, unsigned int maxRow = 4);
	DropDownBox(sf::Texture* texture, sf::Vector2f position, const sf::Font* font = nullptr, unsigned int characterSize = 16, unsigned int maxRow = 4);
	~DropDownBox();

	void update(sf::Vector2f mousePosWindow, bool isButtonPressed);
	void render(sf::RenderTarget* target);

	void push(const std::string& str);
	void setCurrent(unsigned int current);



	const unsigned int& getCurrent();
private:
	sf::RectangleShape rectangle;
	struct properties {
		properties(const std::string name, const sf::FloatRect rect, const sf::Color defaultColor) : name(name), rect(rect), fillColor(defaultColor) {}
		std::string name;
		sf::FloatRect rect;
		sf::Color fillColor;
		sf::Color outlineColor = sf::Color::Black;
	};
	//sf::Vector2f position;
	std::vector< properties> boxs;
	sf::Text text;

	unsigned int currentRow;
	unsigned int maxRow;

	bool show;
};

