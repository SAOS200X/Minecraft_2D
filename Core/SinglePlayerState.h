#pragma once
#include "State.h"
#include "gameSave.h"

class SinglePlayerState :
    public State
{
public:
    SinglePlayerState();
    ~SinglePlayerState();

    void update() override;

    void render(sf::RenderTarget* target) override;

    friend class NewWorldState;
private:
    void initButton();
    void loadGlobalSave(const std::string filePath);

    void updateButtonActive();
 
    std::vector<gameSave> saves;
    std::string pathIndex;

    std::map<std::string, Button*> buttons;

};

