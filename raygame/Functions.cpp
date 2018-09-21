#include "Functions.h"

void DrawingTheScreen(Player& player)
{
	DrawPlayer(player);
	MovePlayer(player);
}

void DrawingRocks(Rock * Arr, int Size)
{
	//InstanciateRock(Arr, &Size);
	DrawRocks(Arr, Size);
	MoveRock(Arr, Size);
}

void DrawingBullet(Bullet * Arr, int Size)
{
	DrawBullet(Arr, Size);
	MoveBullet(Arr, Size);
}

void MovePlayer(Player& player)
{
	if (IsKeyDown(KEY_S))
	{
		player.Position.y += player.Speed;
	}
	if (IsKeyDown(KEY_W))
	{
		player.Position.y -= player.Speed;
	}
	if (IsKeyDown(KEY_D))
	{
		player.Position.x += player.Speed;
	}
	if (IsKeyDown(KEY_A))
	{
		player.Position.x -= player.Speed;
	}

	if (player.Position.x < 0)
		player.Position.x = 0;
	if (player.Position.y < 0)
		player.Position.y = 0;
	if (player.Position.x > (800 - player.Size.x))
		player.Position.x = (800 - player.Size.x);
	if (player.Position.y > (450 - player.Size.y))
		player.Position.y = (450 - player.Size.y);

}
void DrawPlayer(Player& player)
{
	DrawRectangle(player.Position.x, player.Position.y, player.Size.x, player.Size.y, player.color);
}


//Max Rocks is 100 (For now....)
void InstantiateRock(Rock * Arr, int * Size)
{
	int SizeToSpeed = RandomNumber(1, 15);
	Rock newRock{ RandomNumber(1,10),{800,RandomNumber(10, 440)}, GRAY, SizeToSpeed, ((float)SizeToSpeed / 10) * 4 };
	Arr[*Size] = newRock;
	*Size += 1;
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

void InstantiateBullet(Bullet * Arr, int * Size, Player player)
{
	Vector2 TempSize{ RandomNumber(20, 24), RandomNumber(6,10) };
	Bullet newBullet{ RandomNumber(1,3), 5, {player.Position.x + player.Size.x, 
		player.Position.y + (player.Size.y / 2) - (TempSize.y / 2) }, TempSize};
	Arr[*Size] = newBullet;
	*Size += 1;
}
void DrawBullet(Bullet * Arr, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		DrawRectangle(Arr[i].Position.x, Arr[i].Position.y, 24, 6, DARKPURPLE);
	}
}
void MoveBullet(Bullet *Arr, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		Arr[i].Position.x += Arr[i].Speed;
	}
}


int RandomNumber(int min, int max)
{
	return (rand() % max + min);
}