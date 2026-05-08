#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

//#include "Utils.h"
#include "Gui.h"

class Scene 
{
    public:
    virtual void Update(double dt) = 0;
    
};


class GameWindow
{
    public:
    void AddScene(std::string name, std::shared_ptr<Scene> scene)
    {
        scenes.insert({name, scene});
    }

    void Update(double dt)
    {
        activeScene->Update(dt);
    }

    // 1) funkcje związane z zarządzaniem oknem i FPS
    // 2) agregacja i zarządzanie logiką gry (class Game)
    // 3) agregacja i zarządzanie GUI
    // 4) zarządzanie renderem assetów Game (tekstury i dźwięk)
    // 5) przechwytywanie i przekazywanie Inputu z myszy/klawiatury

    void f(int i) const {std::cout << "Printed by GameWindow: " << i << std::endl;}

    void ChangeScene(std::string name) {activeScene = scenes[name];}

    std::map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> activeScene;
};
#endif