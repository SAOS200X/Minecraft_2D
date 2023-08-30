#pragma once

class systemHandle
{
public:

	static const sf::Texture* getTexture(const std::string filePath);
	static const sf::RenderWindow* const getWindow();
	static sf::View* const getView();
	static const sf::Vector2i& getMousePosWindow();
	static const sf::Vector2f& getMousePosView();
	static const sf::Font* const getFont(const unsigned int index = 0);
	static const size_t& getDeltaTime();
	static const bool isButtonPressed(const sf::Mouse::Button button);
	static const bool isKeyPressed(const sf::Keyboard::Key key);
	static const unsigned int getUTFCode();

	friend class Core;
private:
	static void loadTexture(const std::string filePath);
	static void loadFont(const std::string filePath);


	enum class state {release, pressed, hold};
	static std::map<std::string, sf::Texture*> textures;
	static std::vector<sf::Font*> fonts;
	static std::map<sf::Keyboard::Key, systemHandle::state> KeyState;
	static std::map<sf::Mouse::Button, systemHandle::state> MouseState;
	
	static const sf::RenderWindow* window;
	static sf::View* view;
	static sf::Vector2i mousePosWindow;
	static sf::Vector2f mousePosView;
	static size_t* dt;
	static unsigned int utf;
};

