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
#include "MainMenu.h"

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;
	srand(time(NULL));
	//InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");
	SetTargetFPS(60);

	//--------------------------------------------------------------------------------------

	// Main game loop
	bool MainMenu = true;
	int MenuSelection = 0;

	Player player{ 3, DARKBLUE, 4, 0, 0, { 100,100,50,20 } , time(0), 1, 3, 25, "KeyBoard", LoadTexture("Rocket.png") };
	Rock ManyRocks[100]{ 0 };
	Rock ManySmallRocks[100]{ 0 };
	Bullet ManyBullets[100]{ 0 };
	EnemyBullet ManyEnemyBullets[100]{ 0 };
	Star ManyStars[1000]{ 0 };
	Enemy enemies[100]{ 0 };
	
	POWERUP PowerUp = {"Health",1,2};

	PowerUp.Frame = 1;
	PowerUp.MaxFrames = 1;
	/*PowerUp.Rect = { (float)RandomNumber(800,850),
		(float)RandomNumber((PowerUp.Texture.height / 2),(450 - PowerUp.Texture.height)),
		50,50 };
	PowerUp.Texture = LoadTexture("Rocket.png");*/

	int Rocks = 0;
	int SmallRocks = 0;
	int Bullets = 0;
	int EnemyBullets = 0;
	int stars = 0;
	int enemy = 0;
	int MaxEnemiesOnScreen = 5;
	float TIMER = 0;
	int PowerUpCoolDown = 0;
	Vector2 ScoreMultiplyer = {1,0};

	float ShootCooldown = 0;


	//Textures
	Texture2D PlayersTexture = LoadTexture("Rocket.png");
	//Timers
	time_t StarTimer = time(0);
	time_t PlayerTimer = time(0);

	//HideCursor();

	for (int i = 0; i < 250;)
	{
		InstantiateStar(ManyStars, &i);
	}

	LoadGame(&player);
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here

		TIMER++;
		ShootCooldown++;
		PowerUpCoolDown++;
		player.ForceFieldTimer++;



		for (int i = 0; i < 100; i++)
			if(enemies[i].Instantiated)
				enemies[i].Timer++;

		if (IsKeyPressed(KEY_P))
		{
			MainMenu = !MainMenu;
			SaveGame(player);
		}
		if (!MainMenu)
		{

			if (IsMouseButtonPressed(0) && ShootCooldown >= (player.ShootingCooldown))
			{
				InstantiateBullet(ManyBullets, &Bullets, player);
				ShootCooldown = 0;
			}

			//----------------------------------------------------------------------------------
		}
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);




		if (TIMER >= (60 / 1))
		{
			InstantiateRock(ManySmallRocks, &SmallRocks, RandomNumber(3, 6));
			InstantiateRock(ManyRocks, &Rocks, RandomNumber(8, 10));
			TIMER = 0;
		}
		for (int i = 0; i < 100; i++)
		{
			if (enemies[i].Instantiated && time(0) - enemies[i].Time >= enemies[i].FireRate)
			{
				EnemyInstantiateBullet(ManyEnemyBullets, &EnemyBullets, enemies[i]);
				if (ColorToInt(enemies[i].color) == ColorToInt(RED))
					enemies[i].FireRate = (float)RandomNumber(5, 10) / 10;
				if (ColorToInt(enemies[i].color) == ColorToInt(YELLOW))
					enemies[i].FireRate = (float)RandomNumber(10, 20) / 10;
				if (ColorToInt(enemies[i].color) == ColorToInt(GREEN))
					enemies[i].FireRate = (float)RandomNumber(30, 50) / 10;
				enemies[i].Time = time(0);
			}
		}
		if (difftime(time(0), StarTimer) >= 0.2f)
		{
			StarTimer = time(0);
			for (int i = 0; i < 10; i++)
				InstantiateStar(ManyStars, &stars);
			//UpdateStar(ManyStars, 50);
		}
		if (PowerUpCoolDown >= (1200 / 1))
		{
			int RandomPowerUpType = RandomNumber(0,3);
			switch (RandomPowerUpType)
			{
			case 0:
				PowerUp.PowerUpType = "Health";
				PowerUp.UpgradeAmount = 1;
				PowerUp.speed == 2;
				PowerUp.Rect = { 800,
					(float)RandomNumber((PowerUp.Texture.height / 2),(450 - PowerUp.Texture.height)),
					50,50 };
				PowerUp.Texture = LoadTexture("HealthUpgrade.png");
				PowerUp.Frame = 1;
				PowerUp.MaxFrames = 3;
				PowerUp.AnimationTimer = 10;
				break;
			case 1:
				PowerUp.PowerUpType = "Bullet";
				PowerUp.UpgradeAmount = (3 * (player.ShootingCooldown /10));
				PowerUp.speed == 2;
				PowerUp.Rect = { 800,
					(float)RandomNumber((PowerUp.Texture.height / 2),(450 - PowerUp.Texture.height)),
					50,50 };
				PowerUp.Texture = LoadTexture("BulletUpgrade.png");
				PowerUp.Frame = 1;
				PowerUp.MaxFrames = 3;
				PowerUp.AnimationTimer = 10;
				break;
			case 2:
				PowerUp.PowerUpType = "ForceField";
				PowerUp.speed == 2;
				PowerUp.Rect = { 800,
					(float)RandomNumber((PowerUp.Texture.height / 2),(450 - PowerUp.Texture.height)),
					50,50 };
				PowerUp.Texture = LoadTexture("ForceFieldUpgrade.png");
				PowerUp.Frame = 1;
				PowerUp.MaxFrames = 3;
				PowerUp.AnimationTimer = 10;
				break;
			case 3:
				break;
			default:
				break;
			}
			PowerUpCoolDown = 0;
		}


		MoveStar(ManyStars, 1000);
		DrawStar(ManyStars, 1000);
		DrawingTheScreen( ManyRocks, Rocks, ManyBullets, Bullets, ManySmallRocks, SmallRocks);


		if (!MainMenu)
		{
			HideCursor();
			EnemyHandler(enemies, &enemy, ManyBullets, &player.Score,
				&ScoreMultiplyer, MaxEnemiesOnScreen);
			DisplayScore(player.Score, player.HighScore);
			BulletHandler(ManyBullets, &Bullets, enemies);
			EnemyBulletHandler(ManyEnemyBullets, &EnemyBullets);
			PlayerHandler(&player, &player.AnimationTimer, ManyEnemyBullets, enemies);
			PowerUpHandler(&PowerUp,&player);
			//DrawTexture(MouseTexture, GetMouseX(), GetMouseY(), WHITE);
		}
		else
			ShowCursor();
		//DrawFPS(700, 10);

		//DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		if (MainMenu)
		{
			if (DisplayMainMenu(&MenuSelection, &MainMenu, &player))
				return 0;
		}
		EndDrawing();
		//----------------------------------------------------------------------------------
	}


	// De-Initialization
	//-------------------------------------------------------------------------------------- 
	
	CloseWindow();        // Close window and OpenGL context
						  //--------------------------------------------------------------------------------------
	
	return 0;
}