// #include <iostream>
//#include "../raylib/include/raylib.h"
#include "Utils.h"
#include "Game.h"
#include "GameWorld.h"

int main(void)
{
    auto g = std::make_unique<Game>();
    const auto tag = "[MAIN]";
    Log::Msg(tag,"HELLO WHATEVER");
    Player playering;
    Player notsoplayering;
    TileMap tilemap;
    tilemap.tilemap.emplace_back(Tile{0});
    tilemap.tilemap[0].SetOwner(&playering);
    std::cout << tilemap.GetTile(0).building.get() << std::endl;
    tilemap.BuildOnTile(0, &playering, std::make_unique<Building>());
    std::cout << tilemap.GetTile(0).building.get() << std::endl;
    /*Tile tile;
    Player playering;
    tile.CreateBuilding(std::make_unique<Building>());
    std::cout << tile.building.get() << std::endl;
    tile.DestroyBuilding();
    std::cout << tile.building.get() << std::endl;
    std::cout << tile.owner << std::endl;
    tile.SetOwner(&playering);
    std::cout << tile.owner << std::endl;
    std::cout << tile.CanBuild(&playering) << std::endl;
    */
    // g->InitGame();
    // g->GameLoop();
    // const int screenWidth = 800;
    // const int screenHeight = 450;

    // InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // SetTargetFPS(144); 

    // while (!WindowShouldClose())
    // {
    //     BeginDrawing();

    //         ClearBackground(RAYWHITE);

    //         DrawText("Pierwszy tekst", 190, 200, 20, LIGHTGRAY);

    //     EndDrawing();
    // }

    // CloseWindow();

    return 0;
}