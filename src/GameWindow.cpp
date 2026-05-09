#include "../inc/Scenes.h"

#include "raylib.h"

void GameWindow::LaunchGame()
{
    InitWindow(800, 450, "raylib example - basic window");

    AddScene<MainMenuScene>("MainScene");
    ChangeScene("MainScene");
    AddScene<OptionsScene>("OptionsScene");

    MainLoop();

    CloseWindow();
}

void GameWindow::HandleEvent(std::shared_ptr<Event> e)
{
    Log::Msg(tag, e->msgName, " received!");
    auto ptr = std::dynamic_pointer_cast<QuitGameEvent>(e);
    if (ptr != nullptr)
    {
        
        isRunning = false;
        // handle quit game eventl
    }

    auto ptr2 = std::dynamic_pointer_cast<ChangeSceneEvent>(e);
    if (ptr2 != nullptr)
    {
        ChangeScene(ptr2->sceneName);
    }
}

void GameWindow::MainLoop()
{
    // todo: pomiar czasu itd

    while (isRunning)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        UpdateWindowSize();
        Update(0);

        EndDrawing();
    }
}

void GameWindow::UpdateWindowSize()
{
    Vec2i currentSize{GetRenderWidth(), GetRenderHeight()};
    if(currentSize != lastWindowSize)
    {
        auto e = std::make_shared<WindowSizeChangedEvent>();
        e->sender = nullptr;
        e->windowSize = currentSize;
        Broadcast(e);
    }
    lastWindowSize = currentSize;
}
