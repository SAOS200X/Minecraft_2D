#pragma once
#include "MainMenuState.h"

class Core
{
public:

	Core();
	~Core();

	void run();


private:
// -----------------------INIT ------------------------
	void init();
	void initDefault();
	void initFont(std::string filePath);


	void initSettingHandle();
	void initDefaultWindow();
	void initWindow(std::string filePath);
	void initTextures();
	void initSystemHandle();
	void initState();


// -----------------------UPDATE----------------------
	void update();
	void updateKeyPressed();
	void updateInput();
	void updateTextDebug();


// ----------------------RENDER-------------------
	void render();


private:
// ---------------------APP----------------------------
	sf::RenderWindow* defaultWindow;
	sf::RenderWindow* window;
	sf::View* view;
	sf::Event ev;
	sf::Clock clock;

	std::stack<State*> states;

	
// ----------------------VARIANT---------------------
	sf::Int32 dt;

	sf::Font* font;
	sf::Text text;
};

