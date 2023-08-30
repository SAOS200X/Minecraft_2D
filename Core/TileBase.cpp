#include "pch.h"
#include "TileBase.h"
#include "systemHandle.h"

void TileBase::loadTileSheet(const std::string filePath)
{
	if (systemHandle::getTexture(filePath))
	{
		tileSheet = systemHandle::getTexture(filePath);
	}
	else
		logWARNING("couldn't find texture: " + filePath);
}

void TileBase::initTile(const std::string filePath)
{
	std::ifstream INFILE(filePath);
	if (INFILE.is_open())
	{
		std::string token;
		float scale;
		INFILE >> rectsize;
		INFILE >> scale;
		INFILE.ignore();
		gridsize = static_cast<unsigned int>(scale * rectsize);


		std::string name;
		sf::Vector2u pos;
		std::stringstream ss;
		while (std::getline(INFILE, token))
		{
			ss.clear();
			ss.str(token);
			ss >> name;
			ss >> pos.x;
			ss >> pos.y;
			textureName[name] = static_cast<unsigned char>(textureName.size()) + 1;
			textureRect.emplace(std::piecewise_construct, std::forward_as_tuple(textureName[name]),
				std::forward_as_tuple(pos.x * rectsize, pos.y * rectsize, rectsize, rectsize));
		}
		INFILE.close();
	}
	else
		logERROR("couldn't not init tile: " + filePath);
}

void TileBase::initGird()
{
	tile.setSize(static_cast<sf::Vector2f>(sf::Vector2u(gridsize, gridsize)));
	tile.setTexture(tileSheet);


	grid.setSize(static_cast<sf::Vector2f>(sf::Vector2u(gridsize, gridsize)));
	grid.setFillColor(sf::Color::Transparent);
	grid.setOutlineThickness(1.f);
}