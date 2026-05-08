#include "Utils.h"
#include "Game.h"
#include "raylib.h"
#include "Scenes.h"

int main(void)
{
    auto g = std::make_unique<Game>();
    const auto tag = "[MAIN]";

   g->InitGame();
//    g->GameLoop();

    GameWindow gamewindow;
    gamewindow.AddScene("MainScene", std::make_shared<MainMenuScene>());
    gamewindow.activeScene = gamewindow.scenes["MainScene"];
   InitWindow(800, 450, "raylib example - basic window");
   bool openProgram = true;

    while (openProgram)
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            gamewindow.Update(0);
            if(!WindowShouldClose()) {openProgram = true;} else {openProgram = false;}
        EndDrawing();
    }

    CloseWindow();

    return 0;
}