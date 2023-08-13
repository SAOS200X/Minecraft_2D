#pragma once
#include "State.h"
class GameState :
    public State
{
public:
    GameState();
    ~GameState();
    
    void update() override;
    void render(sf::RenderTarget* target) override;

private:
    void init();
    
};

