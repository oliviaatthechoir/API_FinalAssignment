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

#include "raylib.h"
#include "game.h"
#include <iostream>

//TODO: clean up main.cpp, doesn't need that many variables
//TOOD: use RAII for all resources (texture)
//TODO:  make sure you catch your exception! try / catch can go in main, a clean exit is fine. A crash is not. 



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "SPACE INVADERS");

    try
    {
        Resources resources;
        Game game;
        while (WindowShouldClose())
        {
            game.Update();
            game.Render(); 
        }
        
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Fatal error: " << e.what() << "\n"; 
        CloseWindow();
        return 1; 
    }

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    
    BeginDrawing();

    ClearBackground(BLACK);

    EndDrawing();
   
    
    CloseWindow(); 
   

    return 0;
}