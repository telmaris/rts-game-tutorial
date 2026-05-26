#include "../inc/GameWorld.h"

void Tile::CreateBuilding(std::unique_ptr<Building> &&bld)
{
    building = std::move(bld);
    building->placement = this;
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
        Log::Msg("[Tile]", " player is not an owner");
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
        Log::Msg(building->tag, building->id, " Created");
        building->owner = player;
        building->positionId = id;
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

Building* TileMap::GetBuilding(int id)
{
    if(id < 0 || id >= tilemap.size()) return nullptr;
    return tilemap[id].building.get();
}

Building* TileMap::GetBuilding(Vec2i pos)
{
    GetBuilding(GetIdFromCoords(pos));
}

int TileMap::GetIdFromCoords(Vec2i coords)
{
    return (coords.x + coords.y*params.sizeX);
}

Vec2i TileMap::GetCoordsFromId(int id)
{
    return Vec2i{id % params.sizeX, id / params.sizeX};
}

void TileMap::SetTerritory(Vec2i source, int size, Player* player)
{
    // size is a square side length
    if((source.x - size/2) < 0 || (source.x + size/2) >= params.sizeX ||
        (source.y - size/2) < 0 || (source.y + size/2) >= params.sizeY) return;

        Vec2i startingPos{source.x - size/2, source.y - size/2};
        Log::Msg("Set territory", "territory starting pos: ", startingPos.x, " ", startingPos.y);

    for(int x = 0; x < size; x++)
    {
        for(int y = 0; y < size; y++)
        {
            tilemap[GetIdFromCoords({startingPos.x + x, startingPos.y + y})].SetOwner(player);
            // todo: check if neighbouring territory isnt occupied by enemy player
        }
    }
}

// =====================================================

void GameWorld::InitWorld(std::string name, Renderer* r)
{
    worldName = name;
    render = r;
    test = LoadTexture("../assets/textures/test_tex.png");
    // test = LoadTexture("../assets/textures/atlas0.png");

    MapParameters params;
    params.sizeX = 25;
    params.sizeY = 25;

    tilemap.generator.GenerateTileMap(tilemap, params);

    playerHandler.players.insert({0, std::make_unique<Player>(0, tilemap)});
    auto p = playerHandler.players[0].get();

    tilemap.SetTerritory({12,12}, 25, p);
    tilemap[{1,11}].tileType = ResourceType::IRON_ORE;

    auto Mine1 = p->Build<Mine>({1,11});
    auto Storage = p->Build<StorageBuilding>({10,11});

    for(int x = 2; x < 10; x++)
    {
        for(int y = 1; y < 20; y++)
        {
            p->Build<Road>({x,y});
        }
    }

    Mine1->SetReceiver(ResourceType::IRON_ORE, Storage);
}

void GameWorld::Update(double dt)
{
    // update everything like prodution timers, transport, combat, research etc.
    
    // update tilemap with buildings
    tilemap.UpdateBuildings(dt);
    // playerHandler.players[0]->roadNetwork->Update(dt);
    // render->DrawOnLayer(1, test, {100,100});
    // render->DrawOnLayer(2, test, {200,200});
    // render->DrawOnLayer(1, render->atlasMap[0].tex, {0,0});

    for(int x = 0; x < 20; x++)
    {
        for(int y = 0; y < 20; y++)
        {
            render->DrawOnLayer(0, 0, 0, {x*32, y*32});
        }
    }
    // call to render
    // render->DrawOnLayer();
}