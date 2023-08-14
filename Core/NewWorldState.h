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


    std::map<std::string, TextBox*> textBoxs;
};

