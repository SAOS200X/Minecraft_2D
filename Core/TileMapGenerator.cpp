#include "pch.h"
#include "TileMapGenerator.h"

void TileMapGenerator::generator(sf::Vector2i size, std::map<int, std::map<int, TileBase::Tile >>& tileMap, std::map<std::string, unsigned char>& tileName)
{
	unsigned char id = tileName["stone"];
	float SeconeSpawnRate = 0.f;
	unsigned short MaxOre = 0;
	int RNG = 0;

	for (int y = 0; y <= size.y; y++)
		for (int x = 0; x <= size.x; x++)
		{
			if (y < 1)
			{
				id = tileName["grass"];
				MaxOre = 0;
			}
			else if (y < 3)
			{
				id = tileName["dirt"];
				MaxOre = 0;
			}
			else if (y == size.y)
			{
				id = tileName["bedrock"];
				MaxOre = 0;
			}
			else
			{
				RNG = rand() % 15000;

				if ((RNG >= 0) && (RNG < OreRate::DIAMOND))
				{
					id = tileName["diamond_ore"];
					SeconeSpawnRate = 0.64f;
					MaxOre = 5;
				}
				else if ((RNG >= OreRate::DIAMOND) && (RNG < OreRate::EMERALD))
				{
					id = tileName["emerald_ore"];
					SeconeSpawnRate = 0.57f;
					MaxOre = 4;
				}
				else if ((RNG >= OreRate::EMERALD) && (RNG < OreRate::LAPIZ))
				{
					id = tileName["lapiz_ore"];
					SeconeSpawnRate = 0.72f;
					MaxOre = 7;

				}
				else if ((RNG >= OreRate::LAPIZ) && (RNG < OreRate::REDSTONE))
				{
					id = tileName["redstone_ore"];
					SeconeSpawnRate = 0.72f;
					MaxOre = 7;

				}
				else if ((RNG >= OreRate::REDSTONE) && (RNG < OreRate::GOLD))
				{
					id = tileName["gold_ore"];
					SeconeSpawnRate = 0.78f;
					MaxOre = 9;

				}
				else if ((RNG >= OreRate::GOLD) && (RNG < OreRate::IRON))
				{
					id = tileName["iron_ore"];
					SeconeSpawnRate = 0.82f;
					MaxOre = 11;

				}
				else if ((RNG >= OreRate::IRON) && (RNG < OreRate::COAL))
				{
					id = tileName["coal_ore"];
					SeconeSpawnRate = 0.84f;
					MaxOre = 13;

				}
				else if ((RNG >= OreRate::COAL) && (RNG < 500))
				{
					id = 0;
					SeconeSpawnRate = 0.85f;
					MaxOre = 23;
				}
				else
				{
					id = tileName["stone"];
					SeconeSpawnRate = 0.f;
					MaxOre = 0;
				}
			}
			if (MaxOre)
			{
				randomWalk(sf::Vector2i(x, y), SeconeSpawnRate, MaxOre, id, tileMap);
			}
			else if (!tileMap[x].count(y))
				tileMap[x][y].id = id;
		}
}

bool TileMapGenerator::place(sf::Vector2i& pos, float& rate, unsigned short& max, const unsigned short& level, std::vector<sf::Vector2i>& hold)
{
	sf::Vector2i current = pos;
	for (unsigned short i = 0; i < 4; i++)
	{
		current.x = pos.x + (i == 0 ? 1 : (i == 2 ? -1 : 0));
		current.y = pos.y + (i == 1 ? 1 : (i == 3 ? -1 : 0));
		if (rand() % 100 <= (((int)(std::pow(rate, level) * 100) - level * 10)))
		{
			if (std::find(hold.begin(), hold.end(), current) == hold.end())
			{
				hold.push_back(current);
				if (hold.size() >= max)
					return true;
				if (place(current, rate, max, level + 1, hold))
					return true;
			}
		}
	}
	return false;
}
void TileMapGenerator::randomWalk(sf::Vector2i pos, float rate, unsigned short max, unsigned char id, std::map<int, std::map<int, TileBase::Tile>>& tileMap)
{
	std::vector<sf::Vector2i> storage;
	storage.emplace_back(pos);
	place(pos, rate, max, 1, storage);
	for (auto& i : storage)
		if (!tileMap[i.x].count(i.y))
			tileMap[i.x][i.y].id = id;
}
