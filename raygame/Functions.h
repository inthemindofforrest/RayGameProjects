#pragma once
#include <iostream>
#include <time.h>
#include "raylib.h"

class Player
{
public:
	int Health;
	Vector2 Position;
	Color color;
	Vector2 Size;
	float Speed;
};
class Rock
{
public:
	int Health;
	Vector2 Position;
	Color color;
	int Radius;
	int Speed;
};
class Bullet
{
public:
	int Damage;
	int Speed;
	Vector2 Position;
	Vector2 Size;
};

void MovePlayer(Player& player);
void DrawPlayer(Player& player);
void DrawingTheScreen(Player & player);
void InstantiateRock(Rock * Arr, int * Size);
void DrawingRocks(Rock * Arr, int Size);
void DrawRocks(Rock * Arr, int Size);
int RandomNumber(int min, int max);
void MoveRock(Rock * Arr, int Size);
void InstantiateBullet(Bullet * Arr, int * Size, Player player);
void DrawBullet(Bullet * Arr, int Size);
void MoveBullet(Bullet *Arr, int Size);
void DrawingBullet(Bullet * Arr, int Size);
//	int screenWidth = 800;
//  int screenHeight = 450;