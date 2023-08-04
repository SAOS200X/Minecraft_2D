#pragma once
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
	void initWindow();
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

	
// ----------------------VARIANT---------------------
	float dt;
};

