#pragma once
#include "Entity.h"
#include "Inventory.h"

class Player :
    public Entity
{
public:
    Player();
    ~Player();

    void update() override;
    void render(sf::RenderTarget* target) override;
    void Move(float x, float y);

private:
    void initTexture(const std::string filePath);

    sf::RectangleShape shape;
};

