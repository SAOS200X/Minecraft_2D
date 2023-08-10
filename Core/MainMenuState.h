#pragma once
#include "State.h"

class MainMenuState :
    public State
{
public:
    MainMenuState();
    ~MainMenuState();

    void update() override;

    void render(sf::RenderTarget* target) override;

private:
    void initTexture(const std::string filePath);
    void initButton();
    void reinit() override;

    void updateButtonActive();
private:

    std::map<std::string, Button*> buttons;
};

