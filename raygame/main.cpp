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
	Player player{ 100, DARKBLUE, 4, 0, {100,100,50,20} };
	Rock ManyRocks[100]{ 0 };
	Rock ManySmallRocks[100]{ 0 };
	Bullet ManyBullets[100]{ 0 };
	Star ManyStars[1000]{ 0 };
	Enemy enemies[100]{ 0 };


	int Rocks = 0;
	int SmallRocks = 0;
	int Bullets = 0;
	int stars = 0;
	int enemy = 0;
	int MaxEnemiesOnScreen = 5;
	bool IsFullScreen = false;


	//Timers
	time_t start = time(0);
	time_t StarTimer = time(0);

	//HideCursor();

	for (int i = 0; i < 250;)
	{
		InstantiateStar(ManyStars, &i);
	}

	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here


		if (IsKeyPressed(KEY_Q))
		{
			InstantiateBullet(ManyBullets, &Bullets, player);
		}
		if (IsKeyPressed(KEY_P))
		{
			ToggleFullscreen();
			IsFullScreen = !IsFullScreen;
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		if (difftime(time(0), start) >= 1)
		{
			InstantiateRock(ManySmallRocks, &SmallRocks, RandomNumber(3, 6));
			InstantiateRock(ManyRocks, &Rocks, RandomNumber(12, 18));
			start = time(0);
		}
		if (difftime(time(0), StarTimer) >= 0.2f)
		{
			StarTimer = time(0);
			for (int i = 0; i < 10; i++)
				InstantiateStar(ManyStars, &stars);
			//UpdateStar(ManyStars, 50);
		}
		MoveStar(ManyStars, 1000);
		DrawStar(ManyStars, 1000);
		DrawingTheScreen(player, ManyRocks, Rocks, ManyBullets, Bullets, ManySmallRocks, SmallRocks);
		EnemyHandler(enemies, &enemy, ManyBullets, &player.Score, MaxEnemiesOnScreen);
		DisplayScore(player.Score);
		BulletHandler(ManyBullets, &Bullets, enemies);

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