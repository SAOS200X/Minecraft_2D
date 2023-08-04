#pragma once
class State
{
public:
	State();
	~State();

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target) = 0;

protected:
};

