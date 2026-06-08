#ifndef GUI_CONTROLLER_H
#define GUI_CONTROLLER_H

#include "raylib.h"
#include "raymath.h"

class GameScene;

struct CameraMovement
{
    bool isMoving = false;
};

class GuiController
{
    public:

    void Init(GameScene*);
    void Update(double);

    void EscPressed();
    void BuildPressed();

    void LmbPressed();
    void LmbReleased();
    void RmbPressed();
    void RmbReleased();

    private:

        GameScene* scene;
        CameraMovement cameraMovement;
};

#endif