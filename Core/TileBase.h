#pragma once
class TileBase
{
public:
	struct Tile {
		unsigned char id = 0;
		unsigned char state = 0;

		inline operator std::pair<unsigned char, unsigned char>&&() { return { id,state }; }
		inline bool operator==(const std::pair<unsigned char, unsigned char>& right) { return ((id == right.first) && (state == right.second)); }
		inline Tile& operator=(const std::pair<unsigned char, unsigned char>& right) { id = right.first, state = right.second; return *this; }

	};

	friend class GameState;
protected:

	static const unsigned int rectsize;

	static const sf::Texture* tileSheet;
	static std::map<std::string, unsigned char> tileName;
	static std::map<unsigned char, sf::IntRect> tileRect;

	static const sf::Texture* itemSheet;
	static std::map<std::string, unsigned char> itemName;
	static std::map<unsigned char, sf::IntRect> itemRect;

private:
	static void loadTileSheet(const std::string filePath);
	static void initTile(const std::string filePath);

	static void loadItemSheet(const std::string filePath);
	static void initItem(const std::string filePath);

	static void init();
};

