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


	void initSettingHandle();
	void initDefaultWindow();
	void initWindow(std::string filePath);
	void initSystemHandle();
	void initTextures();
	void initFonts();
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
	Timer<> clock;

	std::stack<State*> states;

	
// ----------------------VARIANT---------------------
	size_t dt;

	sf::Text text;
};

