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
    void render(sf::RenderTarget* target) override;

private:
    void initTexture(const std::string filePath);
    void initButton();
    void initDropBoxs();
    void reinit() override;

    void updateButtonActive();
    void applySetting();
private:
    std::map<std::string, DropDownBox*> settings;
    std::map<std::string, Button*> buttons;

};

