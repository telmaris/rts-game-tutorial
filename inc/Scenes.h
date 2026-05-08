#ifndef SCENES_H
#define SCENES_H

#include "GameWindow.h"

class MainMenuScene : public Scene
{
    public: 

    MainMenuScene()
    {
        newGameButton.ChangeText("New Game");
        newGameButton.ChangePosition(200,50);
        newGameButton.func = std::bind(&MainMenuScene::OnNewGamePressed, this);
        loadGameButton.ChangeText("Load Game");
        loadGameButton.ChangePosition(200,150);
        loadGameButton.func = std::bind(&MainMenuScene::OnLoadGamePressed, this);
        optionsButton.ChangeText("Options");
        optionsButton.ChangePosition(200,250);
        optionsButton.func = std::bind(&MainMenuScene::OnOptionsPressed, this);
        quitButton.ChangeText("Quit");
        quitButton.ChangePosition(200,350);
        quitButton.func = std::bind(&MainMenuScene::OnQuitPressed, this);
        //quitobutton
    }

    void Update(double dt) override
    {
        newGameButton.Update(dt);
        loadGameButton.Update(dt);
        optionsButton.Update(dt);
        quitButton.Update(dt);
    }

    void OnNewGamePressed()
    {
        std::cout << "OnNewGamePressed\n";
    }

    void OnLoadGamePressed()
    {
        std::cout << "OnLOADGamePressed\n";
    }
    void OnOptionsPressed()
    {
        std::cout << "OnOPTIOBSPressed\n";
    }
    void OnQuitPressed()
    {
        std::cout << "OnQUITPressed\n";
        
    }

    UiButton newGameButton;
    UiButton loadGameButton;
    UiButton optionsButton;
    UiButton quitButton;
};

#endif