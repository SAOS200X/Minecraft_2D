#pragma once
#include "State.h"
#include "TextBox.h"

class NewWorldState :
    public State
{
public:
    NewWorldState();
    ~NewWorldState();

    void update() override;

    void render(sf::RenderTarget* target) override;

private:
    void initTextBoxs();
    void initButton();

    void updateButtonActive();

    void createNewWorld();


    std::map<std::string, TextBox*> textBoxs;
    std::map<std::string, Button*> buttons;

};

