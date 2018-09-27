#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <string>
#include "raylib.h"

using namespace std;

class Player
{
public:
	int Health;
	Color color;
	float Speed;
	int Score;
	int HighScore;
	Rectangle Rect;
	int AnimationTimer;
	int CurrentFrame = 1;
	int TotalFrames = 3;
	string Shoot;
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
	Rectangle Rect;
	Player player;
};
class EnemyBullet
{
public:
	int Damage;
	int Speed;
	Rectangle Rect;
};
class Star
{
public:
	Vector2 Position;
	double Radius;
	float speed;
};
class Enemy
{
public:
	int Health;
	Color color;
	float Speed;
	Rectangle Rect;
	bool Instantiated;
	Vector2 Origin;
	Vector2 Direction;
	int FireRate;
	time_t Time = time(0);
};

void MovePlayer(Player& player);
void DrawPlayer(Player& player, int * Timer, Texture2D PlayersTexture);
void DrawingTheScreen( Rock * Rocks, int RockSize,
	Bullet * Bullets, int BulletSize, Rock * smallRocks, int smallRockSize);
void InstantiateRock(Rock * Arr, int * Size, int RockSize);
void DrawRocks(Rock * Arr, int Size);
int RandomNumber(int min, int max);
void MoveRock(Rock * Arr, int Size);
void InstantiateBullet(Bullet * Arr, int * Size, Player player);
void DrawBullet(Bullet * Arr, int Size);
void MoveBullet(Bullet *Arr, int Size);
void InstantiateStar(Star * Arr, int * star);
void UpdateStar(Star * Arr, int star);
void DrawStar(Star * Arr, int Size);
void MoveStar(Star *Arr, int Size);
void DisplayScore(int Score, int HigherScore);
void EnemyHandler(Enemy * enemies, int * enemy, Bullet * bullets, int * Score, int maxEnemies);
void InstanciateEnemy(Enemy * enemies, int * enemy, int * Score);
void DrawEnemy(Enemy * enemies);
void BulletHandler(Bullet * bullet, int * bullets, Enemy * enemies);
int GetEnemies(Enemy * enemies);
void Animation(Vector2 Pos, int *Frame, int totalFrames,
	Texture2D texture, int * Timer, float TimePerFrame);
void EnemyMove(Enemy * enemies);
void EnemyMoveBullet(EnemyBullet *Arr, int Size);
void EnemyDrawBullet(EnemyBullet * Arr, int Size);
void EnemyInstantiateBullet(EnemyBullet * Arr, int * Size, Enemy enemies);
void EnemyBulletHandler(EnemyBullet * bullet, int * bullets);
void PlayerHandler(Player* player, int * Timer, EnemyBullet * bullets, Texture2D PlayerTexture);


void LoadGame(Player *player);
void SaveGame(Player player);
//	int screenWidth = 800;
//  int screenHeight = 450;