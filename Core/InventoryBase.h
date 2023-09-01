#pragma once
#include "tileBase.h"
class InventoryBase : 
	public TileBase
{
public:
	InventoryBase(const unsigned short width, const unsigned short height, const float size);

	void drawTile(const unsigned short& x, const unsigned short& y, const float& PosX, const float& PosY, sf::RenderTarget* target);

	void addItem(const std::pair<unsigned char, unsigned char>& item);

	std::pair<unsigned char, unsigned char> removeItem(const unsigned short x, const unsigned short y);
protected:
	sf::Vector2<unsigned short> size;
	sf::RectangleShape item;
	sf::RectangleShape tile;
	std::map<unsigned short, std::map<unsigned short, std::pair<Tile, unsigned short>>> inventory;

	sf::Text text;
};

