#include "pch.h"
#include "TileBase.h"
#include "systemHandle.h"

const unsigned int TileBase::rectsize = 16;

const sf::Texture* TileBase::tileSheet = nullptr;
std::map<std::string, unsigned char> TileBase::tileName;
std::map<unsigned char, sf::IntRect> TileBase::tileRect;

const sf::Texture* TileBase::itemSheet = nullptr;
std::map<std::string, unsigned char> TileBase::itemName;
std::map<unsigned char, sf::IntRect> TileBase::itemRect;

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
			tileName[name] = static_cast<unsigned char>(tileName.size()) + 1;
			tileRect.emplace(std::piecewise_construct, std::forward_as_tuple(tileName[name]),
				std::forward_as_tuple(pos.x * rectsize, pos.y * rectsize, rectsize, rectsize));
		}
		INFILE.close();
	}
	else
		logERROR("couldn't not init tile: " + filePath);
}

void TileBase::loadItemSheet(const std::string filePath)
{
	if (systemHandle::getTexture(filePath))
	{
		itemSheet = systemHandle::getTexture(filePath);
	}
	else
		logWARNING("couldn't find texture: " + filePath);
}

void TileBase::initItem(const std::string filePath)
{
	std::ifstream INFILE(filePath);
	if (INFILE.is_open())
	{
		std::string token;
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
			itemName[name] = static_cast<unsigned char>(itemName.size()) + 1;
			itemRect.emplace(std::piecewise_construct, std::forward_as_tuple(itemName[name]),
				std::forward_as_tuple(pos.x * rectsize, pos.y * rectsize, rectsize, rectsize));
		}
		INFILE.close();
	}
	else
		logERROR("couldn't not init tile: " + filePath);
}

void TileBase::init()
{
	loadTileSheet(m_path::tilesheet);
	loadItemSheet(m_path::itemsheet);
	initTile("resource/init/tile.init");
	initItem("resource/init/item.init");
}
