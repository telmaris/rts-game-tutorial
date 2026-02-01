#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Utils.h"
#include "Player.h"


class Tile
{
    public:
        Tile() = default;
        Tile(int i) : id(i){}
        int id;
        Player* owner = nullptr;  //ten tam ten pointer oznacza wlasciciela tego terytorium
        std::unique_ptr<Building> building;
        void CreateBuilding(std::unique_ptr<Building>&& building);
        void DestroyBuilding();
        void SetOwner(Player* player);
        //bool fajnazgrabnanazwaczymoznazbudowac
        bool CanBuild(Player* player);
};

class TileMap
{
    public:
        TileMap() = default;
        std::vector<Tile> tilemap;
        Tile& GetTile(int id);//Tile pointer bo std::unique_ptr
        void SetTile(int id, Tile&& tile);
        void BuildOnTile(int id, Player* player, std::unique_ptr<Building>&& building);

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