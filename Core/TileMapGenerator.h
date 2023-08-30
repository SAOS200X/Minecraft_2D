#pragma once
#include "TileMap.h"

struct TileMapGenerator
{
public:
	static void generator(sf::Vector2i size, TileBase* tileBase, std::map<int, std::map<int, TileBase::Tile >>& tileMap);
	
private:
	enum OreRate {
		DIAMOND = 10,
		EMERALD = (7 + OreRate::DIAMOND),
		LAPIZ = (25 + OreRate::EMERALD),
		REDSTONE = (41 + OreRate::LAPIZ),
		GOLD = (69 + OreRate::REDSTONE),
		IRON = (100 + OreRate::GOLD),
		COAL = (123 + OreRate::IRON)
	};

	static void randomWalk(sf::Vector2i pos, float rate, unsigned short max, unsigned char id, std::map<int, std::map<int, TileBase::Tile>>& tileMap);

	static bool place(sf::Vector2i& pos, float& rate, unsigned short& max, const unsigned short& level, std::vector<sf::Vector2i>& hold);
};

