#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <string>
#include "raylib.h"

using namespace std;

enum {Beggining_Enemy, Medium_Enemy, Boss_Enemy};


class Controls
{
public:
	int Up_Movement = KEY_W;
	int Down_Movement = KEY_S;
	int Right_Movement = KEY_D;
	int Left_Movement = KEY_A;

	int Main_Shoot = MOUSE_LEFT_BUTTON;
	int Main_Menu = KEY_P;
};

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

	int ShootingCooldown;
	string Shoot;
	int ForceFieldTimer = 600;

	Texture2D Texture = LoadTexture("Rocket.png");
	Texture2D ForceFieldTexture = LoadTexture("ForceFieldUpgrade.png");

	Controls controls;
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

	int EnemyType;


	int Frame = 1;
	int TotalFrames = 3;
	int Timer;
	int deathTimer = 0;
	bool IsDead = false;
	Texture2D Texture = LoadTexture("Alien.png");
};
class POWERUP
{
public:
	string PowerUpType;
	int UpgradeAmount;
	int speed;
	int Frame;
	int MaxFrames;
	int AnimationTimer = 1;
	Rectangle Rect;
	Texture2D Texture;
};

void MovePlayer(Player& player);
void DrawPlayer(Player& player, int * Timer);
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
void EnemyHandler(Enemy * enemies, int * enemy, Bullet * bullets, int Wave,
	Vector2 *scoreMultiplyer, int maxEnemies, int RemainingEnemies,
	int * TotalEnemiesSpawned, int * TotalEnemiesKilled, bool * Boss, bool * MediumEnemy);
void InstanciateEnemy(Enemy * enemies, int * enemy, int Waves, bool * Boss, bool * MediumEnemy);
void DrawEnemy(Enemy * enemies, Vector2 * scoreMultiplyer);
void BulletHandler(Bullet * bullet, int * bullets, Enemy * enemies);
int GetEnemies(Enemy * enemies);
void Animation(Vector2 Pos, int *Frame, int totalFrames,
	Texture2D texture, int * Timer, float TimePerFrame);
void EnemyMove(Enemy * enemies);
void EnemyMoveBullet(EnemyBullet *Arr, int Size);
void EnemyDrawBullet(EnemyBullet * Arr, int Size);
void EnemyInstantiateBullet(EnemyBullet * Arr, int * Size, Enemy enemies);
void EnemyBulletHandler(EnemyBullet * bullet, int * bullets);
void PlayerHandler(Player* player, int * Timer, EnemyBullet * bullets, Enemy *enemies);
void PowerUpHandler(POWERUP *PowerUp, Player *player);
bool AnimateOnce(Vector2 Pos, int *Frame, int totalFrames,
	Texture2D texture, int * Timer, float TimePerFrame);
void LoadGame(Player *player);
void SaveGame(Player player);
//	int screenWidth = 800;
//  int screenHeight = 450;