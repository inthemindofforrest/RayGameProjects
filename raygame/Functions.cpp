#include "Functions.h"

void DrawingTheScreen(Player& player, Rock * Rocks, int RockSize, 
	Bullet * Bullets, int BulletSize, Rock * smallRocks, int smallRockSize)
{
	DrawRocks(smallRocks, smallRockSize);
	MoveRock(smallRocks, smallRockSize);
	DrawPlayer(player);
	MovePlayer(player);
	DrawRocks(Rocks, RockSize);
	MoveRock(Rocks, RockSize);
	

}

void MovePlayer(Player& player)
{
	if (IsKeyDown(KEY_S))
	{
		player.Rect.y += player.Speed;
	}
	if (IsKeyDown(KEY_W))
	{
		player.Rect.y -= player.Speed;
	}
	if (IsKeyDown(KEY_D))
	{
		player.Rect.x += player.Speed;
	}
	if (IsKeyDown(KEY_A))
	{
		player.Rect.x -= player.Speed;
	}

	if (player.Rect.x < 0)
		player.Rect.x = 0;
	if (player.Rect.y < 0)
		player.Rect.y = 0;
	if (player.Rect.x > (800 - player.Rect.width))
		player.Rect.x = (800 - player.Rect.width);
	if (player.Rect.y > (450 - player.Rect.height))
		player.Rect.y = (450 - player.Rect.height);

}
void DrawPlayer(Player& player)
{
	DrawRectangle(player.Rect.x, player.Rect.y, player.Rect.width, player.Rect.height, player.color);
}


//Max Rocks is 100 (For now....)
void InstantiateRock(Rock * Arr, int * Size, int RockSize)
{
	int SizeToSpeed = RockSize;
	Rock newRock{ RandomNumber(3,10),{800,RandomNumber(10, 440)}, 
		GRAY, SizeToSpeed, ((float)SizeToSpeed / 10) * 5 };
	Arr[*Size] = newRock;
	*Size += 1;
	if (*Size >= 100)
		*Size = 0;
}
void DrawRocks(Rock * Arr, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		DrawCircle(Arr[i].Position.x, Arr[i].Position.y, Arr[i].Radius, Arr[i].color);
	}
}
void MoveRock(Rock * Arr, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		Arr[i].Position.x -= Arr[i].Speed;
	}
}

void BulletHandler(Bullet * bullet, int * bullets, Enemy * enemies)
{
	DrawBullet(bullet, *bullets);
	MoveBullet(bullet, *bullets);
}
void InstantiateBullet(Bullet * Arr, int * Size, Player player)
{
	Vector2 TempSize{ 24,6 };
	Bullet newBullet{ RandomNumber(1,3), 5, {player.Rect.x + player.Rect.width,
		player.Rect.y + (player.Rect.height / 2),TempSize.x, TempSize.y}, player };
	Arr[*Size] = newBullet;
	*Size += 1;
	if (*Size >= 100)
		*Size = 0;

}
void DrawBullet(Bullet * Arr, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		DrawRectangle(Arr[i].Rect.x, Arr[i].Rect.y, 
			Arr[i].Rect.width, Arr[i].Rect.height, DARKPURPLE);
	}
}
void MoveBullet(Bullet *Arr, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		Arr[i].Rect.x += Arr[i].Speed;
	}
}

void InstantiateStar(Star * Arr, int * star)
{
	float TempSize{ ((float)RandomNumber(2,20) / 10) };
	Star newStar{ {RandomNumber(800, 1250), RandomNumber(0, 450)}, TempSize, (float)TempSize};
	if (RandomNumber(0, 100) == 99)
	{
		newStar.speed += 10;
		newStar.Position.y = 0;
	}
	Arr[*star] = newStar;
	*star += 1;
	if (*star >= 999)
		*star = 0;
}
void UpdateStar(Star * Arr, int starSize)
{
	for (int star = 0; star < starSize; star++)
		Arr[star].Radius = ((float)RandomNumber(11, 15) / 10);
}
void DrawStar(Star * Arr, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		DrawCircle(Arr[i].Position.x, Arr[i].Position.y, Arr[i].Radius, YELLOW);
	}
}
void MoveStar(Star *Arr, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		Arr[i].Position.x -= Arr[i].speed;
		if(Arr[i].speed > 3)
			Arr[i].Position.y += Arr[i].speed / 5;
	}
}

void DisplayScore(int Score)
{
	string Display = "Score: ";
	Display.append(to_string(Score));
	//char * String = Display.c_str;
	DrawText(Display.c_str(), 370, 20, 25, WHITE);
}

int RandomNumber(int min, int max)
{
	return (rand() % max + min);
}

void EnemyHandler(Enemy * enemies, int * enemy, Bullet * bullets, int * Score, int maxEnemies)
{
	string Health;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (CheckCollisionRecs(bullets[i].Rect, enemies[j].Rect) && enemies[j].Instantiated)
			{
				enemies[j].Health--;
				bullets[i].Rect.height = 0;
				bullets[i].Rect.width = 0;
				bullets[i].Rect.x = 0;
				bullets[i].Rect.y = 0;
				if (enemies[j].Health <= 0)
				{
					if(ColorToInt(enemies[j].color) == ColorToInt(RED))
						*Score += 20;
					else if(ColorToInt(enemies[j].color) == ColorToInt(YELLOW))
						*Score += 10;
					else if (ColorToInt(enemies[j].color) == ColorToInt(GREEN))
						*Score += 2;
					enemies[j].Rect.height = 0;
					enemies[j].Rect.width = 0;
					enemies[j].Rect.x = 0;
					enemies[j].Rect.y = 0;
					enemies[j].Speed = 0;
					enemies[j].Instantiated = false;
					
				}
			}
		}
		Health.append(to_string(enemies[i].Health));
		if (enemies[i].Instantiated)
		{
			DrawText(Health.c_str(), enemies[i].Rect.x + (enemies[i].Rect.width / 2),
				enemies[i].Rect.y - (enemies[i].Rect.height / 2), 10, enemies[i].color);

		}
		Health.clear();
	}
	if (GetEnemies(enemies) < maxEnemies)
	{
		InstanciateEnemy(enemies, enemy, Score);
	}
	DrawEnemy(enemies);
}
void DrawEnemy(Enemy * enemies)
{
	for (int i = 0; i < 100; i++)
		DrawRectangle(enemies[i].Rect.x, enemies[i].Rect.y,
			enemies[i].Rect.width, enemies[i].Rect.height, enemies[i].color);

}
void InstanciateEnemy(Enemy * enemies, int * enemy, int * Score)
{
	if (*Score % 50 == 0 && *Score != 0)
	{
		Enemy newEnemy{ 15, RED, 0, {RandomNumber(300,400),RandomNumber(0,400),
			40,60 }, true };
		enemies[*enemy] = newEnemy;
		enemies[*enemy].Origin.x = newEnemy.Rect.x;
		enemies[*enemy].Origin.y = newEnemy.Rect.y;
		*enemy += 1;
		if (*enemy >= 100)
			*enemy = 0;
	}
	if (*Score % 10 == 0 && *Score % 50 != 0 && *Score != 0)
	{
		Enemy newEnemy{ 10, YELLOW, 0,{ RandomNumber(300,400),RandomNumber(0,400),
			30,50 }, true };
		enemies[*enemy] = newEnemy;
		enemies[*enemy].Origin.x = newEnemy.Rect.x;
		enemies[*enemy].Origin.y = newEnemy.Rect.y;
		*enemy += 1;
		if (*enemy >= 100)
			*enemy = 0;
	}
	else
	{
		Enemy newEnemy{ 3, GREEN, 0,{ RandomNumber(300,400),RandomNumber(0,400),
			20,40 }, true };
		enemies[*enemy] = newEnemy;
		enemies[*enemy].Origin.x = newEnemy.Rect.x;
		enemies[*enemy].Origin.y = newEnemy.Rect.y;
		*enemy += 1;
		if (*enemy >= 100)
			*enemy = 0;
	}
	
}

void EnemyMove(Enemy * enemies)
{
	for (int i = 0; i < 100; i++)
	{
		
	}
}

int GetEnemies(Enemy * enemies)
{
	int Total = 0;

	for (int i = 0; i < 100; i++)
	{
		if (enemies[i].Instantiated)
			Total++;
	}
	return Total;
}