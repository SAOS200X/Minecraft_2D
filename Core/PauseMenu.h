#pragma once
#include "State.h"

class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	void update();
	void render(sf::RenderTarget* target);

	inline void pause() { show = !show; }
	inline const bool isPause() const { return show; }
	inline const bool isSave() const { return save; }

private:
	void initBackGround();
	void initButton();
	void updateButtonActive();

	sf::RectangleShape bg;
	std::map<std::string, Button*> buttons;
	bool show;
	bool save;
};

