#include "../inc/GameWorld.h"

void Tile::CreateBuilding(std::unique_ptr<Building> &&bld)
{
    building = std::move(bld);
    building->InitBuilding(tileType);
}

void Tile::DestroyBuilding()
{
    building = nullptr;
}

void Tile::SetOwner(Player *player)
{
    owner = player;
}

bool Tile::CanBuild(Player *player)
{
    bool allowed = true;
    if (player != owner)
    {
        allowed = false;
    }
    if (building != nullptr)
    {
        allowed = false;
    }
    return allowed;
}

Tile &TileMap::GetTile(int id)
{
    return tilemap[id];
}

void TileMap::SetTile(int id, Tile &&tile)
{
    tilemap[id] = std::move(tile);
}

void TileMap::BuildOnTile(int id, Player *player, std::unique_ptr<Building> &&building)
{
    Tile &tile = tilemap[id];
    if (tile.CanBuild(player))
    {
        Log::Msg(building->tag, building->id, "Created");
        tile.CreateBuilding(std::move(building));
    }
}

void TileMap::UpdateBuildings(double dt)
{
    for(auto& tile : tilemap)
    {
        if(tile.building != nullptr) tile.building->Update(dt);
    }
}

void GameWorld::InitWorld()
{
    // initialite the tile     
    tilemap = std::make_unique<TileMap>();
    tilemap->tilemap.emplace_back(0);
    Player p{0x1000, tilemap.get()};
    tilemap->tilemap[0].SetOwner(&p);
    
    p.Build<Woodcutter>(0);
}

void GameWorld::Update(double dt)
{
    // update everything like prodution timers, transport, combat, research etc.

    // update tilemap with buildings
    tilemap->UpdateBuildings(dt);

}