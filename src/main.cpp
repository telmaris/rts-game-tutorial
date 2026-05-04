#include "Utils.h"
#include "Game.h"
#include "raylib.h"

int main(void)
{
    auto g = std::make_unique<Game>();
    const auto tag = "[MAIN]";

   g->InitGame();
//    g->GameLoop();

   InitWindow(800, 450, "raylib example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}