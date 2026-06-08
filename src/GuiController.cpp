#include "../inc/Scenes.h"

void InputProcessor::HandleInputs()
{
    if(IsActionPressed(CLOSE_TOP_GUI)) controller->EscPressed(); 
    if(IsActionPressed(OPEN_BUILD_GUI)) controller->BuildPressed();
    if(IsActionPressed(LEFT_BUTTON_DOWN)) controller->LmbPressed();
    if(IsActionReleased(LEFT_BUTTON_DOWN))  controller->LmbReleased();
    if(IsActionPressed(RIGHT_BUTTON_DOWN)) controller->RmbPressed();
    if(IsActionReleased(RIGHT_BUTTON_DOWN)) controller->RmbReleased(); 
}

void GuiController::Init(GameScene* s)
{
    scene = s;
}

void GuiController::Update(double dt)
{
    if(cameraMovement.isMoving)
    {
        Vector2 delta = GetMouseDelta();
        delta.x *= -1;
        auto pos = Vector2Clamp(Vector2Add(scene->render.camera.target, delta), {0,-scene->game->tilemap.params.sizeY*64 + 1080}, {scene->game->tilemap.params.sizeX*64 - 1920, 0});
        scene->render.camera.target = pos;
        Log::Msg("[GuiController]", "mouse pos: ", scene->render.camera.target.x, " ", scene->render.camera.target.y);
    }
}

void GuiController::EscPressed()
{
    auto msg = std::make_shared<ChangeSceneEvent>();
    msg->sender = scene;
    msg->sceneName = "GameMenuScene";
    scene->broker->Broadcast(msg);
    
    Log::Msg("[Input]", "escape pressed");
}

void GuiController::BuildPressed()
{
    Log::Msg("[Input]", "Q pressed");
}

void GuiController::LmbPressed()
{
    auto pos = GetMousePosition();
    pos.x += scene->render.camera.target.x;
    pos.y -= scene->render.camera.target.y;

    Vec2i tilePos{pos.x/64, pos.y/64};
    auto& tile = scene->game->tilemap[tilePos];

    Log::Msg("[Input]", "Tile ID: ", tile.id, " clicked!");

    if(tile.building != nullptr)
    {
        Log::Msg("[Input]", tile.building->name, " selected!");
    }
}

void GuiController::LmbReleased()
{
    // Log::Msg("[Input]", "LMB  released");
}

void GuiController::RmbPressed()
{
    cameraMovement.isMoving = true;

    // Log::Msg("[Input]", "RMB pressed");
}

void GuiController::RmbReleased()
{
    cameraMovement.isMoving = false;
    // Log::Msg("[Input]", "RMB released");
}