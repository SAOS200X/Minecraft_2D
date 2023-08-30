#include "pch.h"
#include "TileMap.h"
#include "systemHandle.h"
#include "TileMapGenerator.h"

TileMap::TileMap()
{
	init();
}

void TileMap::update()
{
	sf::Vector2f f = systemHandle::getMousePosView() / gridsize;
	f.x = std::floor(f.x), f.y = std::floor(f.y);
	this->grid.setPosition(f * gridsize);

	mineBlock(static_cast<int>(f.x), static_cast<int>(f.y));
}

void TileMap::render(sf::RenderTarget* target)
{
	 sf::IntRect bound(static_cast<sf::Vector2i>(systemHandle::getView()->getCenter() - systemHandle::getView()->getSize() / 2.f) / this->gridsize,
		static_cast<sf::Vector2i>(systemHandle::getView()->getSize()) / this->gridsize);

	 for (int x = bound.left; x <= bound.left + bound.width; x++)
		 for (int y = bound.top; y <= bound.top + bound.height; y++)
			 drawTile(x, y, target);

	target->draw(this->grid);
}

const bool TileMap::loadSave(std::stringstream& infile)
{
	int x = 0, y = 0;
	unsigned char id = 0;

	while (infile.peek() != EOF)
	{
		infile >> x >> y;
		infile.ignore();
		id = infile.get();
		infile.ignore();

		tileMap[x][y].id = id;
		changeSave[x][y] = id;
	}

	return (x || y || id);
}

void TileMap::saveTile(std::ofstream& outfile)
{
	if (changeSave.size())
	{
		outfile << "\n";
		for (auto& x : changeSave)
			for (auto& y : x.second)
				outfile << x.first << " " << y.first << " " << y.second << " ";
		outfile.seekp(-1, std::ios::end);
		outfile.put(EOF);
	}
}

void TileMap::init()
{
	this->loadTileSheet(m_path::tilesheet);
	this->initTile("resource/init/tile.init");
	this->initGird();

	TileMapGenerator::generator(sf::Vector2i(60, 35), static_cast<TileBase*>(this), tileMap);
}

void TileMap::drawTile(const int& x, const int& y, sf::RenderTarget*& target)
{
	if (tileMap[x].size() && tileMap[x][y].id)
	{
		this->tile.setTextureRect(this->textureRect[tileMap[x][y].id]);
		this->tile.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)) * this->gridsize);
		target->draw(this->tile);
		if (tileMap[x][y].state)
		{
			std::stringstream ss; ss << "crack_" << static_cast<unsigned short>(tileMap[x][y].state);
			this->tile.setTextureRect(this->textureRect[this->textureName[ss.str()]]);
			target->draw(this->tile);
		}
	}
}

void TileMap::mineBlock(int x, int y)
{
	static long long delay = 15000;
	if (clock.getEslapseTime() > delay && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (tileMap[x].size() && tileMap[x][y].id)
		{
			if (tileMap[x][y].state++ > 9)
			{
				tileMap[x].erase(y);
				changeSave[x][y] = 0;
			}
		}
		clock.restart();
	}
}



