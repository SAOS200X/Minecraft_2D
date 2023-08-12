#pragma once
#include "State.h"
class SinglePlayerState :
    public State
{
public:
    SinglePlayerState();
    ~SinglePlayerState();

    void update() override;

    void render(sf::RenderTarget* target) override;

private:
    void initTexture(const std::string filePath);
    void initButton();

    void updateButtonActive();
    void reinit() override;


    std::map<std::string, Button*> buttons;

};

