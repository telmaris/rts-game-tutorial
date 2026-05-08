#ifndef GUI_H
#define GUI_H

#include "Utils.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

class UiWidget
{
    public:

    virtual void Update(double dt) = 0;

    void ChangePosition(int x, int y)
    {
        pos.x = x;
        pos.y = y;
    }
    void ChangeSize(int sizeX, int sizeY)
    {
        size.x = sizeX;
        size.y = sizeY;
    }
    
    Vec2i pos{100, 100};
    Vec2i size{200, 100};
    
};

class UiButton : public UiWidget
{
    public:
    
    void Update(double dt) override
    {
        if(GuiButton((Rectangle){pos.x,pos.y,size.x,size.y}, text.c_str())) OnClick();
    }
    void ChangeText(std::string stryng)
    {
        text = stryng;
    }

    virtual void OnClick() {func();}
    
    std::string text{"Default button text"};
    std::function<void()> func;
    int number;
};

#endif