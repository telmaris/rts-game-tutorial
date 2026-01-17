#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Utils.h"
#include "Player.h"

class Tile
{
    public:
        Tile() = default;
};

class TileMap
{
    public:
        TileMap() = default;

};

class MapGenerator
{
    public:
        MapGenerator() = default;

        std::unique_ptr<TileMap> GenerateTileMap();
};

class PlayerHandler
{
    public:
        PlayerHandler() = default;

    private:
        std::map<int, std::unique_ptr<Player>> players;
};

class GameWorld
{
    public:
        GameWorld() = default;

        void InitWorld();
        void Update();

    private:
        std::unique_ptr<TileMap> tilemap;
        MapGenerator generator;
        PlayerHandler playerHandler;
};


#endif