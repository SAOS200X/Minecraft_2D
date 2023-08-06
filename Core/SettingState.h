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
    void initDropBoxs(std::string filePath);
    void addDropBox(sf::Vector2f size, sf::Vector2f position, std::vector<std::string>& tokens, unsigned short current);

    void applySetting();

private:
    std::map<std::string, DropDownBox*> settings;
    std::map<std::string, Button*> buttons;

};

