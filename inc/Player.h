#ifndef PLAYER_H
#define PLAYER_H

#include "Utils.h"
#include "InputHandler.h"

class TileMap;

class Player
{
    public:
        Player() = default;

    private:
        std::unique_ptr<InputHandler> input;
        TileMap* tilemap;
};

class HumanPlayer : public Player
{
    public:
        HumanPlayer() = default;
};


#endif