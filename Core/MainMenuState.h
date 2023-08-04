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
};

