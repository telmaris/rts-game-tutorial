// #include <iostream>
//#include "../raylib/include/raylib.h"
#include "Utils.h"
#include "Game.h"

int main(void)
{
    auto g = std::make_unique<Game>();
    const auto tag = "[MAIN]";
    
   g->InitGame();
   g->GameLoop();

    return 0;
}