#include "../inc/Scenes.h"

MainMenuScene::MainMenuScene()
{
    auto newGameButton = std::make_shared<UiButton>();
    newGameButton->ChangeText("New Game");
    newGameButton->func = std::bind(&MainMenuScene::OnNewGamePressed, this);
    buttonsColumn.AddChild(newGameButton);

    auto loadGameButton = std::make_shared<UiButton>();
    loadGameButton->ChangeText("Load Game");
    loadGameButton->func = std::bind(&MainMenuScene::OnLoadGamePressed, this);
    buttonsColumn.AddChild(loadGameButton);

    auto optionsButton = std::make_shared<UiButton>();
    optionsButton->ChangeText("Options");
    optionsButton->func = std::bind(&MainMenuScene::OnOptionsPressed, this);
    buttonsColumn.AddChild(optionsButton);

    auto quitButton = std::make_shared<UiButton>();
    quitButton->ChangeText("Quit");
    quitButton->func = std::bind(&MainMenuScene::OnQuitPressed, this);
    buttonsColumn.AddChild(quitButton);
}

void MainMenuScene::Update(double dt)
{
    // newGameButton.Update(dt);
    // loadGameButton.Update(dt);
    // optionsButton.Update(dt);
    // quitButton.Update(dt);
    buttonsColumn.Update(dt);
}

void MainMenuScene::OnNewGamePressed()
{
    std::cout << "OnNewGamePressed\n";
}

void MainMenuScene::OnLoadGamePressed()
{
    std::cout << "OnLOADGamePressed\n";
}

void MainMenuScene::OnOptionsPressed()
{
    auto msg = std::make_shared<ChangeSceneEvent>();
    msg->sender = this;
    msg->sceneName = "OptionsScene";
    broker->Broadcast(msg);
}

void MainMenuScene::OnQuitPressed()
{
    auto msg = std::make_shared<QuitGameEvent>();
    msg->sender = this;
    broker->Broadcast(msg);
}

void MainMenuScene::HandleEvent(std::shared_ptr<Event> e)
{
    auto ptr = std::dynamic_pointer_cast<WindowSizeChangedEvent>(e);
    if (ptr != nullptr)
    {
        buttonsColumn.UpdateSize(ptr->windowSize);
    }
}



// ============ OPTIONS ================

OptionsScene::OptionsScene()
{
    backButton.ChangeText("Back");
    backButton.ChangePosition(200, 50);
    backButton.func = std::bind(&OptionsScene::OnBackPressed, this);
}

void OptionsScene::Update(double dt)
{
    backButton.Update(dt);
}

void OptionsScene::OnBackPressed()
{
    auto msg = std::make_shared<ChangeSceneEvent>();
    msg->sender = this;
    msg->sceneName = "MainScene";
    broker->Broadcast(msg);
}