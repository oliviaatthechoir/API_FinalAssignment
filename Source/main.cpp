/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*b
*   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "game.h"
#include "Window.h"
#include <iostream>
#include <string_view>
using namespace std::string_view_literals; 
//TOOD: use RAII for all resources (texture)



int main(void)
{   
    try
    {
        Window window("SPACE INVADERS");
        Game game;
        while (!WindowShouldClose())
        {
            game.Update();
            game.Render(); 
    
        }        
    }
    catch (const TextureLoadException& e)
    {
        std::cerr << "Load failed: " << e.what() << "\n";            
    }//TODO: catch runtime_error and, always a good idea, std::exception and ...
    catch (...) {
        std::cerr << "bajs";
    }
   

    return 0;
}