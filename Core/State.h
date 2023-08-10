#pragma once
#include "Button.h"

class State
{
public:
	State();
	virtual ~State() = 0;

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target) = 0;

	friend class Core;
	friend class SettingState;

protected:
	static std::stack<State*>* states;
	sf::Texture* texture;
	sf::Sprite sprite;


	virtual void reinit() = 0;
};

