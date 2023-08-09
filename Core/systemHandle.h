#pragma once

class systemHandle
{
public:

	static const sf::RenderWindow* const getWindow();
	static const sf::Vector2i& getMousePosWindow();
	static const sf::Font* const getFont();
	static const INT32* const getDeltaTime();

	friend class Core;
private:
	enum state {release, pressed, hold};
	static std::map<unsigned short, systemHandle::state> KeyState;
	static std::map<unsigned short, systemHandle::state> MouseState;
	
	static const sf::RenderWindow* window;
	static sf::Font* font;
	static sf::Vector2i mousePosWindow;
	static INT32* dt;
};

