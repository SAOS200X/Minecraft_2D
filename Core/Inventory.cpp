#include "pch.h"
#include "Inventory.h"
#include "systemHandle.h"

Inventory::Inventory()
	: InventoryBase(9, 4, 60.f)
{
	init();
}

void Inventory::update()
{
	if (systemHandle::isKeyPressed(sf::Keyboard::E))
	{
		open = !open;
		swapPos = { -1, -1 };
	}
	for (int i = 1; i <= 9; i++)
		if (systemHandle::isKeyPressed(sf::Keyboard::Key(26 + i)))
		{
			select = i;
			break;
		}
	if (open)
	{
		short x = std::floor((systemHandle::getMousePosWindow().x - 0.2f * gridSize) / gridSize);
		short y = std::floor((systemHandle::getMousePosWindow().y - 0.2f * gridSize) / gridSize);
		if (systemHandle::isButtonPressed(sf::Mouse::Left) && swap && (x >= 0 && x < size.x) && (y >= 0 && y < size.y))
		{
			hover = true;
			swap = false;
			if (inventory[swapPos.y].count(swapPos.x))
			{
				auto i = this->inventory[swapPos.y][swapPos.x];
				this->inventory[swapPos.y][swapPos.x] = this->inventory[y][x];
				this->inventory[y][x] = i;
			}
			swapPos = { -1, -1 };
		}
		else if ((x >= 0 && x < size.x) && (y >= 0 && y < size.y))
		{
			hover = true;
			if (systemHandle::isButtonPressed(sf::Mouse::Left))
			{
				swap = true;
				swapPos = { x,y };
			}
		}
		else
			hover = false;
	}

}

void Inventory::render(sf::RenderTarget* target)
{
	grid.setOutlineColor(sf::Color(0, 0, 0, 100));
	for (unsigned short x = 0; x < size.x; x++)
	{
		grid.setPosition(grid.getSize().x * (0.8f + x), grid.getSize().y * 0.8f);
		target->draw(grid);
		this->drawTile(x, 0, grid.getPosition().x, grid.getPosition().y, target);
	}

	if (open)
	{
		grid.setOutlineColor(sf::Color(200, 200, 200, 100));
		for (unsigned short y = 1; y < size.y; y++)
			for (unsigned short x = 0; x < size.x; x++)
			{
				grid.setPosition(grid.getSize().x * (0.8f + x), grid.getSize().y * (0.8f + y));
				target->draw(grid);
				this->drawTile(x, y, grid.getPosition().x, grid.getPosition().y, target);
			}
	}

	grid.setOutlineColor(sf::Color(250, 50, 50, 100));
	if (select)
		grid.setPosition(gridSize * (0.8f + select - 1), gridSize * 0.8f), target->draw(grid);
	if (open && hover)
		grid.setPosition(gridSize * (0.8f + static_cast<short>(std::floor((systemHandle::getMousePosWindow().x - 0.2f * gridSize) / gridSize))),
			gridSize * (0.8f + static_cast<short>(std::floor((systemHandle::getMousePosWindow().y - 0.2f * gridSize) / gridSize)))), target->draw(grid);
	if (swap && open)
		grid.setPosition(gridSize * (0.8f + swapPos.x), gridSize * (0.8f + swapPos.y)), target->draw(grid);
}

void Inventory::init()
{
	select = 0;
	open = false;
	hover = false;
	size.x = 9;
	size.y = 4;
	gridSize = 60.f;
	grid.setSize(Vector2<float>(gridSize));
	grid.setFillColor(sf::Color::Transparent);
	grid.setOutlineThickness(4.f);
	grid.setOutlineColor(sf::Color(0, 0, 0, 100));
	grid.setOrigin(grid.getSize() / 2.f);
	//inventory = std::make_unique<InventoryBase>(size.x, size.y, gridSize);
}
