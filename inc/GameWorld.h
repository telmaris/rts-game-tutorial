#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Utils.h"
#include "MapGenerator.h"


class PlayerHandler
{
    public:
        PlayerHandler() = default;

        std::map<int, std::unique_ptr<Player>> players;
};

class GameWorld
{
    public:
        GameWorld() = default;

        void InitWorld();
        void Update(double);

    
        TileMap tilemap;
        PlayerHandler playerHandler;
};


#endif