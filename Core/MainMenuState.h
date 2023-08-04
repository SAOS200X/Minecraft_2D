#pragma once
#include "State.h"

class MainMenuState :
    public State
{
public:
    MainMenuState();
    ~MainMenuState();

    void update() override;
    void updateButton();

    void render(sf::RenderTarget* target) override;

private:
    void initTexture(std::string filePath);
    void initButton();

private:
    sf::Texture* texture;
    sf::Sprite backGround;

    std::vector<Button*> buttons;
};

