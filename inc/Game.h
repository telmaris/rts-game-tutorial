#ifndef GAME_H
#define GAME_H

#include "Utils.h"
#include "Window.h"

// fasada gry
class Game
{
public:
    Game() = default;
    ~Game() = default;

    void InitGame();
    void GameLoop();
    void Cleanup();

private:
    std::unique_ptr<Window> window;
    
};


#endif