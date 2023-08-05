#pragma once
#include "State.h"
#include "DropDownBox.h"
class SettingState :
    public State
{
public:
    SettingState();
    ~SettingState();

    void update() override;
    void updateButtonActive();

    void render(sf::RenderTarget* target) override;

private:
    void initTexture(std::string filePath);
    void initButton();
    void initDropBox();

private:
    std::map<std::string, DropDownBox*> settings;

};

