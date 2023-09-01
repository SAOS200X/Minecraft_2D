#pragma once
#include "TileBase.h"

class TileMap : public TileBase
{
public:
	TileMap();

	void update();
	void render(sf::RenderTarget* target);

	const bool loadSave(std::stringstream& infile);
	std::pair<unsigned char, unsigned char> mineBlock(const float& x, const float& y);

	void saveTile(std::ofstream& outfile);

private:
	void init();
	void initDrop(const std::string& filePath);
	void initGird();
	void drawTile(const int& x, const int& y, sf::RenderTarget* target);
	std::pair<unsigned char, unsigned char> mineBlock(const int& x, const int& y);

	sf::RectangleShape tile;
	std::map<unsigned char, std::pair<unsigned char, unsigned char>> drop;
	std::map<int, std::map<int, Tile>> tileMap;
	std::map<int, std::map<int, unsigned char>> changeSave;


	///////// DEBUG ////////////////
	Timer<> clock;
	sf::Vector2i mousePosGrid;
	const unsigned int gridsize = 48;
	sf::RectangleShape grid;
};

