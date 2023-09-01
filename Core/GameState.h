#pragma once
#include "State.h"
#include "gameSave.h"
#include "Player.h"
#include "TileMap.h"
#include "PauseMenu.h"
#include "gameSave.h"

class GameState :
    public State
{
private:
    struct savePropertite
    {
        std::string filePath;
        std::string seed;
        time_t dateCreate;
        time_t dateCount;
        time_t total;
    } m_p;

public:
    GameState(const std::string& filePath);
    ~GameState();
    
    void update() override;
    void render(sf::RenderTarget* target) override;

private:
    void init();
    void loadSave(const std::string& filePath);

    void updateMoving();
    void saveWorld();
    
    std::unique_ptr<Player> player;
    std::unique_ptr<TileMap> tileMap;
    std::unique_ptr<PauseMenu> pmenu;
    std::unique_ptr<Inventory> inventory;
};

