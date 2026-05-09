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

        void OnBackPressed();

        UiButton backButton;
};

#endif