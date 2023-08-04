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
	void initDefaultWindow();
	void initWindow(std::string filePath);
	void initState();


	void loadSetting();

// -----------------------UPDATE----------------------
	void updateInput();

	void update();

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
	float dt;
};

