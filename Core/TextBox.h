#pragma once
class TextBox
{
public:

	TextBox(const sf::Vector2f size, const sf::Vector2f position, const sf::Color color, const sf::Font* font, const unsigned int characterSize = 16);
	TextBox(const sf::Texture* texture, const sf::Vector2f position, const sf::Font* font, const unsigned int characterSize = 16);

	~TextBox();


	void update(const sf::Vector2f mousePosWindow, const bool isButtonPressed);
	void render(sf::RenderTarget* target);

	void typed(const unsigned int utf);

	template<typename T>
	inline void setString(const T str);
	inline const std::string& getString() { return str; }
private:
	sf::RectangleShape sprite;
	sf::Text text;
	std::string str;
	
	bool select;
};

template<typename T>
inline void TextBox::setString(const T str)
{
	std::stringstream ss;
	ss << str;
	this->str = ss.str();
}
