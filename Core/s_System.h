#pragma once

class s_System
{
public:

	static const sf::RenderWindow const* getWindow();
	static const sf::Vector2i& getMousePosWindow();

	friend class Core;
private:
	enum state {release, pressed, hold};
	static std::map<unsigned short, s_System::state> KeyState;
	static std::map<unsigned short, s_System::state> MouseState;
	
	static sf::RenderWindow const* window;
	static sf::Font* font;
	static sf::Vector2i mousePosWindow;
};

