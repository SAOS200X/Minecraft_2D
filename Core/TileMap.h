#pragma once
#include "TileBase.h"

class TileMap : public TileBase
{
public:
	TileMap();

	void update();
	void render(sf::RenderTarget* target);
	const bool loadSave(std::stringstream& infile);
	void saveTile(std::ofstream& outfile);

private:
	void init();
	void drawTile(const int& x, const int& y, sf::RenderTarget*& target);
	void mineBlock(int x, int y);

	std::map<int, std::map<int, Tile>> tileMap;
	std::map<int, std::map<int, unsigned char>> changeSave;


	///////// DEBUG ////////////////
	Timer<> clock;
	sf::Vector2i mousePosGrid;
};

