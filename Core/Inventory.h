#pragma once
#include "InventoryBase.h"
class Inventory :
	public InventoryBase
{
public:
	Inventory();
	void update();

	void render(sf::RenderTarget* target);

private:
	void init();

	sf::Vector2<unsigned short> size;
	float gridSize;
	sf::RectangleShape grid;
	//std::unique_ptr<InventoryBase> inventory;

	unsigned short select;
	bool open;
	sf::Vector2<short> swapPos;
	bool swap;
	bool hover;
};

