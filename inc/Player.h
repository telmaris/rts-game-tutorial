#ifndef PLAYER_H
#define PLAYER_H

#include "Utils.h"
#include "InputHandler.h"
#include "Building.h"
#include "BuildingFactory.h"

class TileMap;

class Player
{
public:
    Player() = default;
    Player(int i, TileMap *tmap) : tilemap(tmap), id(i), build(this, tilemap){}

    template <typename T>
    void Build(int tilePos)
    {
        static_assert(std::is_base_of<Building, T>::value);
        build.Build<T>(tilePos);
    }

    int id;

private:
    std::unique_ptr<InputHandler> input;
    TileMap *tilemap;
    BFactory build; // initialize BuildingFactory with current player
};

class HumanPlayer : public Player
{
public:
    HumanPlayer() = default;
};

#endif