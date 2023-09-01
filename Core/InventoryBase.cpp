#include "pch.h"
#include "InventoryBase.h"
#include "systemHandle.h"

InventoryBase::InventoryBase(const unsigned short width, const unsigned short height, const float size)
{
	this->size.x = width;
	this->size.y = height;
	item.setSize(Vector2<float>(size));
	item.setOrigin(item.getSize() / 2.f);
	tile = item;

	item.setTexture(this->itemSheet);
	tile.setTexture(this->tileSheet);

	tile.setScale(0.8f, 0.8f);

	text.setFont(*systemHandle::getFont());
	text.setCharacterSize(size / 3);
	text.setOrigin(-size / 4.f, -size / 4.f);
}


void InventoryBase::drawTile(const unsigned short& x, const unsigned short& y, const float& PosX, const float& PosY, sf::RenderTarget* target)
{
	if (inventory[y].count(x) && inventory[y][x].first.id)
	{
		if (inventory[y][x].first.state)
		{
			item.setTextureRect(this->itemRect[inventory[y][x].first.id]);
			item.setPosition(PosX, PosY);
			target->draw(item);
		}
		else
		{
			tile.setTextureRect(this->tileRect[inventory[y][x].first.id]);
			tile.setPosition(PosX, PosY);
			target->draw(tile);
		}

		text.setString(std::to_string(inventory[y][x].second));
		text.setPosition(PosX, PosY);
		target->draw(text);
	}
}

void InventoryBase::addItem(const std::pair<unsigned char, unsigned char>& item)
{
	if (!item.second)
		return;
	for (auto& i : inventory)
		for (auto& j : i.second)
			if ((j.second.first.state == item.first) && (j.second.first.id == item.second))
			{
				if (j.second.second > 63)
					continue;
				else
				{
					j.second.second++;
					return;
				}
			}
	
	for (unsigned short y = 0; y < size.y; y++)
		for (unsigned short x = 0; x < size.x; x++)
		{
			if (!inventory[y].count(x))
			{
				inventory[y][x].first.state = item.first;
				inventory[y][x].first.id = item.second;
				inventory[y][x].second = 1;
				return;
			}
		}

}

std::pair<unsigned char, unsigned char> InventoryBase::removeItem(const unsigned short x, const unsigned short y)
{
	if (inventory[y].size() && inventory[y][x].second > 1)
	{
		inventory[y][x].second--;
		return inventory[y][x].first;
	}
	else
	{
		auto i = inventory[y][x].first;
		inventory[y].erase(x);
		return i;
	}
}

