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

//TODO: clean up main.cpp, doesn't need that many variables
//  Delete redundant code: raylib has collision code (rect rect intersection is all you need), raylib is GetRandom for random numbers, 
//TODO: move each strut / class into a separate file (physical structure). Just header file is fine
//TOOD: use RAII for all resources (texture)
//TODO: simplify all implementations. use range-for, algoritms (erase_if)
//      reduce nesting, dont use type flags ("is_enemy_bullet") just keep two separate list of projectiles, one for player, one for alien shots)
//TODO:     make sure you catch your exception! try / catch can go in main, a clean exit is fine. A crash is not. 



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

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Game game;
    Resources resources;
    game.resources = resources;
    game.Launch();

    
    //--------------------------------------------------------------------------------------

  
   

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        game.Update();
      

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

       

        game.Render();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

   

    return 0;
}