#include "pch.h"
#include "TileMap.h"
#include "systemHandle.h"
#include "TileMapGenerator.h"

TileMap::TileMap()
{
	init();
	initGird();
}

void TileMap::update()
{
	sf::Vector2f f = systemHandle::getMousePosView() / gridsize;
	f.x = std::floor(f.x), f.y = std::floor(f.y);
	grid.setPosition(f * gridsize);
}

void TileMap::render(sf::RenderTarget* target)
{
	 sf::IntRect bound(static_cast<sf::Vector2i>(systemHandle::getView()->getCenter() - systemHandle::getView()->getSize() / 2.f) / gridsize,
		static_cast<sf::Vector2i>(systemHandle::getView()->getSize()) / gridsize);

	 for (int x = bound.left; x <= bound.left + bound.width; x++)
		 for (int y = bound.top; y <= bound.top + bound.height; y++)
			 drawTile(x, y, target);

	target->draw(grid);
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

std::pair<unsigned char, unsigned char> TileMap::mineBlock(const float& x, const float& y)
{
	return std::move(mineBlock(static_cast<int>(x / gridsize), static_cast<int>(y / gridsize)));
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
	tile.setSize(Vector2<float>(gridsize));
	tile.setTexture(this->tileSheet);
	initDrop("resource/init/mine.init");
	TileMapGenerator::generator(sf::Vector2i(60, 35), tileMap, this->tileName);
}

void TileMap::initDrop(const std::string& filePath)
{
	std::ifstream INFILE(filePath);
	if (INFILE.is_open())
	{
		std::stringstream ss;
		std::string token, name, type, id;

		while (std::getline(INFILE, token))
		{
			ss.clear();
			ss.str(token);
			ss >> name >> type >> id;
			if (type == "tile")
				drop.emplace(std::piecewise_construct, std::forward_as_tuple(this->tileName[name]), std::forward_as_tuple(0, this->tileName[id]));
			else if (type == "item")
				drop.emplace(std::piecewise_construct, std::forward_as_tuple(this->tileName[name]), std::forward_as_tuple(1, this->itemName[id]));
		}
		INFILE.close();
	}
	else
		logERROR("couldn't not init drop: " + filePath);
}

void TileMap::initGird()
{
	tile.setSize(static_cast<sf::Vector2f>(sf::Vector2u(gridsize, gridsize)));
	tile.setTexture(tileSheet);


	grid.setSize(static_cast<sf::Vector2f>(sf::Vector2u(gridsize, gridsize)));
	grid.setFillColor(sf::Color::Transparent);
	grid.setOutlineThickness(1.f);
}

void TileMap::drawTile(const int& x, const int& y, sf::RenderTarget* target)
{
	if (tileMap[x].size() && tileMap[x][y].id)
	{
		tile.setTextureRect(this->tileRect[tileMap[x][y].id]);
		tile.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)) * gridsize);
		target->draw(tile);
		if (tileMap[x][y].state)
		{
			std::stringstream ss; ss << "crack_" << static_cast<unsigned short>(tileMap[x][y].state);
			tile.setTextureRect(this->tileRect[this->tileName[ss.str()]]);
			target->draw(tile);
		}
	}
}

std::pair<unsigned char, unsigned char> TileMap::mineBlock(const int& x, const int& y)
{
	static long long delay = 15000;
	if (clock.getEslapseTime() > delay && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		clock.restart();
		if (tileMap[x].size() && tileMap[x][y].id)
		{
			if (tileMap[x][y].state++ > 9)
			{
				changeSave[x][y] = 0;
				auto i = tileMap[x][y].id;
				tileMap[x].erase(y);
				if (drop.count(i))
					return drop[i];
				else
					return { 0, i };
			}
		}
	}
	return {};
}



