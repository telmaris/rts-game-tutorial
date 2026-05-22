#include "../inc/Scenes.h"

MainMenuScene::MainMenuScene()
{
    buttonsColumn.ChangeSizeAnchor(Vec2f{0.2f, 0.4f});

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
    backButton.ChangePositionAnchor(Vec2f{0.5f, 0.7f});
    backButton.func = std::bind(&OptionsScene::OnBackPressed, this);

    fullScreenCheckBox.ChangeText("Fullscreen");
    fullScreenCheckBox.ChangePositionAnchor(Vec2f{0.4f, 0.4f});

    masterVolume.ChangeText("Music Volume");
    masterVolume.ChangePositionAnchor(Vec2f{0.4f, 0.5f});
}

void OptionsScene::Update(double dt)
{
    backButton.Update(dt);
    fullScreenCheckBox.Update(dt);
    masterVolume.Update(dt);

    if(fullScreenCheckBox.HasChanged())
    {
        // send toggle fullscreen event
        auto msg = std::make_shared<ToggleFullscreenEvent>();
        msg->sender = this;
        broker->Broadcast(msg);

        if(fullScreenCheckBox.IsActive())
        {
            std::cout << "Fullscreen activated!\n";
        }
        else std::cout << "Fullscreen disabled!\n";
    }

    if(masterVolume.HasChanged())
    {
        std::cout << "Master volume: " << masterVolume.GetValue() << std::endl;
    }
}

void OptionsScene::OnBackPressed()
{
    auto msg = std::make_shared<ChangeSceneEvent>();
    msg->sender = this;
    msg->sceneName = "MainScene";
    broker->Broadcast(msg);
}

void OptionsScene::HandleEvent(std::shared_ptr<Event> e)
{
    auto ptr = std::dynamic_pointer_cast<WindowSizeChangedEvent>(e);
    if (ptr != nullptr)
    {
        backButton.UpdateSize(ptr->windowSize);
        fullScreenCheckBox.UpdateSize(ptr->windowSize);
        masterVolume.UpdateSize(ptr->windowSize);
    }
}

// =========== NEW GAME ================

NewGameScene::NewGameScene()
{
    backButton.ChangeText("Back");
    backButton.ChangePositionAnchor(Vec2f{0.5f, 0.7f});
    backButton.func = std::bind(&NewGameScene::OnBackPressed, this);
}

void NewGameScene::Update(double dt)
{
    backButton.Update(dt);
}

void NewGameScene::OnBackPressed()
{
    auto msg = std::make_shared<ChangeSceneEvent>();
    msg->sender = this;
    msg->sceneName = "MainScene";
    broker->Broadcast(msg);
}

void NewGameScene::HandleEvent(std::shared_ptr<Event> e)
{
    auto ptr = std::dynamic_pointer_cast<WindowSizeChangedEvent>(e);
    if (ptr != nullptr)
    {
        backButton.UpdateSize(ptr->windowSize);
    }
}



// ============== LOAD GAME ==============