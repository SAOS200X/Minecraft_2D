#pragma once
class TileBase
{
public:

	friend struct TileMapGenerator;
protected:
	struct Tile {
		unsigned char id = 0;
		unsigned char state = 0;
	};

	sf::RectangleShape tile;
	sf::RectangleShape grid;

	const sf::Texture* tileSheet = nullptr;
	std::map<std::string, unsigned char> textureName;
	std::map<unsigned char, sf::IntRect> textureRect;
	unsigned int gridsize = 0;
	unsigned int rectsize = 0;

	void loadTileSheet(const std::string filePath);
	void initTile(const std::string filePath);
	void initGird();
};

