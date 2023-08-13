#pragma once
#include "Button.h"

class State
{
public:
	State();
	virtual ~State();

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target) = 0;

	friend class Core;
	friend class SettingState;

protected:
	void initBackground(const std::string filePath);

	static std::stack<State*>* states;
	sf::Texture* texture;
	sf::Sprite sprite;

};

