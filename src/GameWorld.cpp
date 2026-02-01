#include "../inc/GameWorld.h"

void Tile::CreateBuilding(std::unique_ptr<Building>&& bld)
{
    building = std::move(bld);
}
void Tile::DestroyBuilding()
{
    building = nullptr;
}
void Tile::SetOwner(Player* player)
{
    owner = player;
}
bool Tile::CanBuild(Player* player) 
{
    bool allowed = true;
    if(player != owner) {allowed = false;}
    if(building != nullptr) {allowed = false;}
    return allowed;
}
Tile& TileMap::GetTile(int id)
{
    return tilemap[id];
}
void TileMap::SetTile(int id, Tile&& tile)
{
    tilemap[id] = std::move(tile);
}
void TileMap::BuildOnTile(int id, Player* player, std::unique_ptr<Building>&& building)
{
    Tile& tile = tilemap[id];
    if(tile.CanBuild(player)) {tile.CreateBuilding(std::move(building));}
}