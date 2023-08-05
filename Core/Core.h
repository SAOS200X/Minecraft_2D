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
	void initDefaultWindow();
	void initWindow(std::string filePath);
	void initState();
	void initSystem();


// -----------------------UPDATE----------------------
	void update();
	void updateInput();
	void updateTextDebug();


// ----------------------RENDER-------------------
	void render();


private:
// ---------------------APP----------------------------
	sf::RenderWindow* DefaultWindow;
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

