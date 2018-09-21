/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "Functions.h"

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;
	srand(time(NULL));
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	Player player{ 100,{ 100,100 }, DARKBLUE,{ 50,20 }, 4 };
	Rock ManyRocks[100]{ 0 };
	Bullet ManyBullets[100]{ 0 };
	int Rocks = 0;
	int Bullets = 0;
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		DrawingTheScreen(player);

		if (IsKeyPressed(KEY_E))
			InstantiateRock(ManyRocks, &Rocks);

		if (IsKeyPressed(KEY_Q))
			InstantiateBullet(ManyBullets, &Bullets, player);

		DrawingRocks(ManyRocks, Rocks);
		DrawingBullet(ManyBullets, Bullets);
		//DrawFPS(700, 10);
		
		//DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}