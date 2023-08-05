#pragma once
#include "State.h"

class MainMenuState :
    public State
{
public:
    MainMenuState();
    ~MainMenuState();

    void update() override;
    void updateButtonActive();

    void render(sf::RenderTarget* target) override;

private:
    void initTexture(std::string filePath);
    void initButton();

private:
    sf::Texture* texture;
    sf::Sprite backGround;

    std::map<std::string, Button*> buttons;
};

