#ifndef SCENES_H
#define SCENES_H

#include "GameWindow.h"
#include "Gui.h"


class MainMenuScene : public Scene
{
    public: 

    MainMenuScene();

    void Update(double dt) override;

    void OnNewGamePressed();
    void OnLoadGamePressed();
    void OnOptionsPressed();
    void OnQuitPressed();

    void HandleEvent(std::shared_ptr<Event>) override;

    // UiButton newGameButton;
    // UiButton loadGameButton;
    // UiButton optionsButton;
    // UiButton quitButton;
    VBox buttonsColumn;
};

class OptionsScene : public Scene
{
    public:

        OptionsScene();
        void Update(double dt) override;
        void HandleEvent(std::shared_ptr<Event>) override;

        void OnBackPressed();

        UiButton backButton;
        CheckBox fullScreenCheckBox;
        SliderBar masterVolume;
};

class NewGameScene : public Scene
{
    public:

        NewGameScene();
        void Update(double dt) override;
        void HandleEvent(std::shared_ptr<Event>) override;

        void OnBackPressed();
        void OnStartPressed();

        UiButton backButton;
        TextBox gameName;
        // add dropdownbox with map size
        UiButton startGame;
};

class LoadGameScene : public Scene
{
    public:

        LoadGameScene();
        void Update(double dt) override;
        void HandleEvent(std::shared_ptr<Event>) override;

        void OnBackPressed();
        void LoadSaves();
        void OnSavePressed(std::string);

        UiButton backButton;
        VBox saveButtons;
};

class GameScene : public Scene
{
    public:

        GameScene();
        void Update(double dt) override;
        void HandleEvent(std::shared_ptr<Event>) override;

        void StartNewGame(std::string, MapParameters);
        void LoadGame(std::string);
        void SaveGame();

        void OnBackPressed();

        UiButton backButton;
        std::unique_ptr<GameWorld> game{nullptr};

};

#endif