#include "../inc/Gui.h"

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void UiButton::Update(double dt)
{
    if (GuiButton((Rectangle){pos.x, pos.y, size.x, size.y}, text.c_str()))
        OnClick();
}

void VBox::Update(double dt)
{
    for(auto& child : children)
    {
        child->Update(dt);
    }
}