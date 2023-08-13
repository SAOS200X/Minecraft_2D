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
    struct save {
        std::string name;
        std::string filePath;
        sf::RectangleShape icon;
    };
    std::vector<save> saves;

    void initButton();
    void loadGlobalSave(const std::string filePath);

    void updateButtonActive();
 

    std::map<std::string, Button*> buttons;

};

