#ifndef GUI_H
#define GUI_H

#include "Utils.h"


class UiWidget
{
    public:

    virtual void Update(double dt) = 0;

    inline void ChangePosition(int x, int y)
    {
        pos.x = x;
        pos.y = y;
    }
    inline void ChangeSize(int sizeX, int sizeY)
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
    
    void Update(double dt) override;
   inline  void ChangeText(std::string stryng)
    {
        text = stryng;
    }

    virtual void OnClick() {func();}
    
    std::string text{"Default button text"};
    std::function<void()> func;
    int number;
};

class VBox : public UiWidget
{
    public:

    void Update(double dt) override;

    inline void UpdateSize(Vec2i windowSize)
    {
        pos = Vec2i{windowSize.x * posAnchor.x, windowSize.y * posAnchor.y};
        size = Vec2i{windowSize.x * sizeAnchor.x, windowSize.y * sizeAnchor.y};

        int childrenCount = children.size();
        Vec2i childrenSize{size.x, size.y / childrenCount};

        for(int i = 0; i < childrenCount; i++)
        {
            children[i]->size = childrenSize;
            children[i]->pos = Vec2i{pos.x, pos.y + (childrenSize.y + margins.y) * i};
        }
    }

    void UpdateSize()
    {
        int childrenCount = children.size();
        Vec2i childrenSize{size.x, size.y / childrenCount};

        for(int i = 0; i < childrenCount; i++)
        {
            children[i]->size = childrenSize;
            children[i]->pos = Vec2i{pos.x, pos.y + (childrenSize.y + margins.y) * i};
        }
    }

    void AddChild(std::shared_ptr<UiWidget> child)
    {
        children.push_back(child);
        UpdateSize();
    }

    std::vector<std::shared_ptr<UiWidget>> children;

    Vec2f posAnchor{0.2f, 0.2f};
    Vec2f sizeAnchor{0.1f, 0.3f};
    Vec4i margins{0, 5, 0, 0};  // up down left right
};

#endif