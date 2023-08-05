#pragma once
#include "Button.h"

class State
{
public:
	State();
	~State();

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target) = 0;

	friend class Core;

protected:
	static std::stack<State*>* states;
	sf::Texture* texture;
	sf::Sprite sprite;
};

