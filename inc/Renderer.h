#ifndef RENDERER_H
#define RENDERER_H

#include "Utils.h"
#include "raylib.h"
#include "Gui.h"

struct CanvasLayer
{
    CanvasLayer()
    {
        fbo = LoadRenderTexture(1920, 1080);
    }

    RenderTexture2D fbo;    // frame buffer object
};

struct TextureAtlas
{
    inline void LoadTextureAtlas(const char* path)
    {
        tex = LoadTexture(path);
        size = {32,32};
        dim = {tex.width / size.x, tex.height / size.y};
    }

    Rectangle GetRectFromId(int id)
    {
        Rectangle rect;

        rect.height = size.y;
        rect.width = size.x;

        rect.x = (id % dim.x) * rect.width;
        rect.y = (id / dim.y) * rect.height;

        return rect;
    }

    Texture2D tex;
    Vec2i size;
    Vec2i dim;  // {columns, rows}
};

class Renderer
{
    public:

    void Draw(std::vector<UiWidget*> ui = {}, double dt = 0);
    void DrawOnLayer(int, Texture2D, Vec2i);
    void DrawOnLayer(int, int, int, Vec2f);
    void ClearLayers();


    std::vector<CanvasLayer> layers{4};
    std::map<int, TextureAtlas> atlasMap;
};



#endif