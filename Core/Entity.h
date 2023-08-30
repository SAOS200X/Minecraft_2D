#pragma once
class Entity
{
public:
	Entity();

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target) = 0;


protected:
	sf::Texture* texture;
	sf::RectangleShape shape;
};

