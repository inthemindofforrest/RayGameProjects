#include "Functions.h"

void DrawingTheScreen( Rock * Rocks, int RockSize,
	Bullet * Bullets, int BulletSize, Rock * smallRocks, int smallRockSize)
{
	DrawRocks(smallRocks, smallRockSize);
	MoveRock(smallRocks, smallRockSize);
	DrawRocks(Rocks, RockSize);
	MoveRock(Rocks, RockSize);
}

void PlayerHandler(Player* player, int * Timer, EnemyBullet * bullets, Enemy *enemies)
{
	DrawPlayer(*player, Timer);
	MovePlayer(*player);
	for (int i = 0; i < 100; i++)
	{
		if (CheckCollisionRecs(bullets[i].Rect, (*player).Rect))
		{

			bullets[i].Rect.x = 0;
			bullets[i].Rect.y = 0;
			if((*player).ForceFieldTimer > 600)
				(*player).Health--;
		}
	}
	if ((*player).Health <= 0)
	{
		int HighScore = 0;
		string Movement = (*player).Shoot;
		Player ResetPlayer{ 3, DARKBLUE, 4, 0,0,{ 100,100,50,20 } , time(0) };
		if ((*player).Score > (*player).HighScore)
			HighScore = (*player).Score;

		(*player) = ResetPlayer;
		(*player).HighScore = HighScore;
		(*player).Shoot = Movement;

		SetMousePosition({ 100,100 });

		for (int i = 0; i < 100; i++)
		{
			enemies[i].Instantiated = false;
		}

		SaveGame(*player);
	}
	if ((*player).Health > 3)
		(*player).Health = 3;
}

void MovePlayer(Player& player)
{
	if (player.Shoot == "KeyBoard")
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
	}
	

	if (player.Shoot == "Mouse")
	{
		player.Rect.y = GetMouseY();
		player.Rect.x = GetMouseX();
		if (player.Rect.x < 10.0f)
			SetMousePosition({ 10.0f,(float)GetMouseY() });
		if (player.Rect.y < 10.0f)
			SetMousePosition({ (float)GetMouseX() ,10.0f });
		if (player.Rect.x > (350.0f - player.Rect.width))
			SetMousePosition({ (350.0f - player.Rect.width),(float)GetMouseY() });
		if (player.Rect.y > (440.0f - player.Rect.height))
			SetMousePosition({ (float)GetMouseX(),(440.0f - player.Rect.height) });
	}
	if (player.Rect.x < 10.0f)
	{
		player.Rect.x = 10.0f;
	}
	if (player.Rect.y < 10.0f)
	{
		player.Rect.y = 10.0f;
	}
	if (player.Rect.x >(350.0f - player.Rect.width))
	{
		player.Rect.x = (350.0f - player.Rect.width);
	}
	if (player.Rect.y > (440.0f - player.Rect.height))
	{
		player.Rect.y = (440.0f - player.Rect.height);
	}
}
void DrawPlayer(Player& player, int * Timer)
{
	//23x8
	Animation({ player.Rect.x, player.Rect.y }, &player.CurrentFrame,
	player.TotalFrames, player.Texture, Timer, 10);
	//DrawRectangle(player.Rect.x, player.Rect.y, player.Rect.width, player.Rect.height, player.color);
	//Draw Health of the player
	for (int i = 0; i < player.Health; i++)
	{
		DrawRectangle(10 + (i * 20) + 5, 430, 10, 10, RED);
	}
	

	if(player.ForceFieldTimer < 600)
		Animation({ player.Rect.x - ((player.ForceFieldTexture.width / 3) / 2) + (player.Rect.width / 2), 
			player.Rect.y - ((player.ForceFieldTexture.height) / 2) + (player.Rect.height / 2) },
			&player.CurrentFrame,
			player.TotalFrames, player.ForceFieldTexture, Timer, 10);
		//DrawTexture(player.ForceFieldTexture, player.Rect.x, player.Rect.y, WHITE);

}


void InstantiateRock(Rock * Arr, int * Size, int RockSize)
{
	int SizeToSpeed = RockSize;
	Rock newRock{ RandomNumber(3,10),{ 800,RandomNumber(10, 440) },
		DARKGRAY, SizeToSpeed, ((float)SizeToSpeed / 10) * 5 };
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
	Bullet newBullet{ RandomNumber(1,3), 5,{ player.Rect.x + player.Rect.width,
		player.Rect.y + (player.Rect.height / 2),TempSize.x, TempSize.y }, player };
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
	Star newStar{ { RandomNumber(800, 1250), RandomNumber(0, 450) }, TempSize, (float)TempSize };
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
		if (Arr[i].speed > 3)
			Arr[i].Position.y += Arr[i].speed / 5;
	}
}

void DisplayScore(int Score, int HigherScore)
{
	string Display = "Score: ";
	Display.append(to_string(Score));

	string HighScore = "High Score: ";
	HighScore.append(to_string(HigherScore));
	//char * String = Display.c_str;
	if (HigherScore >= Score)
	{
		DrawText(Display.c_str(), 370, 20, 25, WHITE);
		DrawText(HighScore.c_str(), 500, 30, 15, GREEN);
	}
	else
	{
		DrawText(Display.c_str(), 370, 20, 25, GREEN);
		DrawText(HighScore.c_str(), 500, 30, 15, DARKGRAY);
	}
}

int RandomNumber(int min, int max)
{
	return (rand() % max + min);
}
int RandomNumberNegToPos(int min, int max)
{
	int Operation = RandomNumber(0, 1);
	if(Operation)
		return (rand() % max + min);
	else
		return (rand() % max + min) * - 1;
}

void EnemyHandler(Enemy * enemies, int * enemy, Bullet * bullets, int * Score,Vector2 *scoreMultiplyer, int maxEnemies)
{
	string Health;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (enemies[j].Instantiated)
			{
				if (enemies[j].Health < 0)
					enemies[j].Health == 0;
				if (CheckCollisionRecs(bullets[i].Rect, enemies[j].Rect))
				{
					enemies[j].Health--;
					bullets[i].Rect.height = 0;
					bullets[i].Rect.width = 0;
					bullets[i].Rect.x = 0;
					bullets[i].Rect.y = 0;
					if (enemies[j].Health <= 0)
					{
						if (ColorToInt(enemies[j].color) == ColorToInt(RED))
							*Score += 20;
						else if (ColorToInt(enemies[j].color) == ColorToInt(YELLOW))
							*Score += 10;
						else if (ColorToInt(enemies[j].color) == ColorToInt(GREEN))
							*Score += 2;
						(*scoreMultiplyer).y = j;
						enemies[j].Texture = LoadTexture("AlienDeath.png");
					}
				}
				if (enemies[j].Rect.y >= (450 - enemies[i].Rect.height) && enemies[i].IsDead == false)
				{
					enemies[j].Texture = LoadTexture("AlienDeathDissolve.png");
					enemies[j].TotalFrames = 6;
					enemies[j].IsDead = true;
				}
			

				for (int k = 0; k < 100; k++)
				{
					if (CheckCollisionRecs(enemies[j].Rect, enemies[k].Rect) && k != j &&
						enemies[j].Health <= 0)
					{
						if (enemies[k].Health > 0)
						{
							*Score += 2 * (*scoreMultiplyer).x;
							(*scoreMultiplyer).x++;
						}
						enemies[k].Health = 0;
						
					}
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
	EnemyMove(enemies);
	DrawEnemy(enemies, scoreMultiplyer);
}
void DrawEnemy(Enemy * enemies, Vector2 * scoreMultiplyer)
{
	for (int i = 0; i < 100; i++)
		/*DrawRectangle(enemies[i].Rect.x, enemies[i].Rect.y,
			enemies[i].Rect.width, enemies[i].Rect.height, enemies[i].color);*/
		if (enemies[i].Instantiated)
		{
			if (enemies[i].IsDead == false)
				Animation({ enemies[i].Rect.x, enemies[i].Rect.y }, &enemies[i].Frame,
					enemies[i].TotalFrames, enemies[i].Texture, &enemies[i].Timer, 10);
			else
				if (AnimateOnce({ enemies[i].Rect.x, enemies[i].Rect.y }, &enemies[i].Frame,
					enemies[i].TotalFrames, enemies[i].Texture, &enemies[i].Timer, 10))
				{
					enemies[i].Instantiated = false;
					enemies[i].IsDead = true;
					enemies[i].TotalFrames = 3;
					if ((*scoreMultiplyer).y == i)
					{
						(*scoreMultiplyer).y = 0;
						(*scoreMultiplyer).x = 0;
					}

				}
		}
}
void InstanciateEnemy(Enemy * enemies, int * enemy, int * Score)
{
	if (*Score % 50 == 0 && *Score != 0)
	{
		Enemy newEnemy{ 15, RED, (float)RandomNumber(1,3) / 3,{ RandomNumber(350,400),RandomNumber(100,250),
			40,60 }, true,{ newEnemy.Rect.x, newEnemy.Rect.y },{ 0,0 }, RandomNumber(1,5), time(0) };
		enemies[*enemy] = newEnemy;
		enemies[*enemy].Origin.x = newEnemy.Rect.x;
		enemies[*enemy].Origin.y = newEnemy.Rect.y;
		enemies[*enemy].Texture = LoadTexture("StrongestAlien.png");
		
		*enemy += 1;
		if (*enemy >= 100)
			*enemy = 0;
	}
	if (*Score % 10 == 0 && *Score % 50 != 0 && *Score != 0)
	{
		Enemy newEnemy{ 10, YELLOW, (float)RandomNumber(1,3) / 3,{ RandomNumber(350,400),RandomNumber(0,400),
			30,50 }, true,{ newEnemy.Rect.x, newEnemy.Rect.y },{ 0,0 }, RandomNumber(1,5), time(0) };
		enemies[*enemy] = newEnemy;
		enemies[*enemy].Origin.x = newEnemy.Rect.x;
		enemies[*enemy].Origin.y = newEnemy.Rect.y;
		enemies[*enemy].Texture = LoadTexture("StrongerAlien.png");
		*enemy += 1;
		
		if (*enemy >= 100)
			*enemy = 0;
	}
	else
	{
		Enemy newEnemy{ 3, GREEN, (float)RandomNumber(1,3) / 3,{ RandomNumber(350,400),RandomNumber(0,400),
			20,40 }, true ,{ newEnemy.Rect.x, newEnemy.Rect.y },{ 0,0 }, RandomNumber(1,5), time(0) };
		enemies[*enemy] = newEnemy;
		*enemy += 1;
		if (*enemy >= 100)
			*enemy = 0;
	}

}

void EnemyMove(Enemy * enemies)
{
	for (int i = 0; i < 100; i++)
	{
		if (enemies[i].Instantiated)
		{
			if (enemies[i].Health > 0 && enemies[i].Rect.y < (450 - enemies[i].Rect.height))
			{
				enemies[i].Rect.y += enemies[i].Speed;
				if (enemies[i].Rect.y > enemies[i].Origin.y + (abs(enemies[i].Speed) * 20) || enemies[i].Rect.y < enemies[i].Origin.y - (abs(enemies[i].Speed) * 20))
				{

					enemies[i].Speed *= -1;
				}
				if (enemies[i].Rect.y > 440)
				{
					enemies[i].Rect.y = 440;
				}
				if (enemies[i].Rect.y < 10)
				{
					enemies[i].Rect.y = 10;
				}
			}
			else if (enemies[i].Health <= 0 && enemies[i].Rect.y < (450 - enemies[i].Rect.height))
			{
				enemies[i].Speed = abs(enemies[i].Speed);
				enemies[i].Rect.y += enemies[i].Speed * 2;
				enemies[i].Rect.x -= enemies[i].Speed * 2;
			}
			else
			{
				enemies[i].deathTimer++;
			}
		}
	}
}
void EnemyBulletHandler(EnemyBullet * bullet, int * bullets)
{
	EnemyDrawBullet(bullet, *bullets);
	EnemyMoveBullet(bullet, *bullets);
}
void EnemyInstantiateBullet(EnemyBullet * Arr, int * Size, Enemy enemies)
{
	Vector2 TempSize{ 24,6 };
	if (enemies.Health > 0)
	{
		EnemyBullet newBullet{ RandomNumber(1,3), 5,{ enemies.Rect.x - enemies.Rect.width - (Arr[*Size].Rect.width / 2),
			enemies.Rect.y + (enemies.Rect.height / 2),TempSize.x, TempSize.y } };
		Arr[*Size] = newBullet;
		*Size += 1;
		if (*Size >= 100)
			*Size = 0;
	}
}
void EnemyDrawBullet(EnemyBullet * Arr, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		DrawRectangle(Arr[i].Rect.x, Arr[i].Rect.y,
			Arr[i].Rect.width, Arr[i].Rect.height, RED);
		
	}
}
void EnemyMoveBullet(EnemyBullet *Arr, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		Arr[i].Rect.x -= Arr[i].Speed;
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

void Animation(Vector2 Pos, int *Frame, int totalFrames,
	Texture2D texture, int * Timer, float TimePerFrame)
{
	if (*Timer >= TimePerFrame)
	{
		if (*Frame > totalFrames)
			*Frame = 1;
		(*Frame)++;
		*Timer = 0;
	}
	Rectangle Source = { ((texture.width / totalFrames)* (*Frame)), 0, 
		(texture.width / totalFrames) , texture.height };
	DrawTextureRec(texture, Source, { Pos.x, Pos.y }, WHITE);
	(*Timer)++;
}

bool AnimateOnce(Vector2 Pos, int *Frame, int totalFrames,
	Texture2D texture, int * Timer, float TimePerFrame)
{
	if (*Timer >= TimePerFrame)
	{
		(*Frame)++;
		*Timer = 0;
	}
	Rectangle Source = { ((texture.width / totalFrames)* (*Frame)), 0,
		(texture.width / totalFrames) , texture.height };
	DrawTextureRec(texture, Source, { Pos.x, Pos.y }, WHITE);
	(*Timer)++;

	if (*Frame == totalFrames)
		return true;
}

void PowerUpHandler(POWERUP *PowerUp, Player *player)
{

	(*PowerUp).Rect.x -= (*PowerUp).speed;
	Animation({ (*PowerUp).Rect.x, (*PowerUp).Rect.y }, 
		&(*PowerUp).Frame, (*PowerUp).MaxFrames,
		(*PowerUp).Texture, &(*PowerUp).AnimationTimer, 7);

	if (CheckCollisionRecs((*PowerUp).Rect, (*player).Rect))
	{
		if ((*PowerUp).PowerUpType == "Health")
		{
			(*player).Health += (*PowerUp).UpgradeAmount;
			(*PowerUp).Rect.x = 0;
			(*PowerUp).Rect.y = 0;
			(*PowerUp).Rect.width = 0;
			(*PowerUp).Rect.height = 0;
		}
		if ((*PowerUp).PowerUpType == "Bullet")
		{
			(*player).ShootingCooldown -= (*PowerUp).UpgradeAmount;
			(*PowerUp).Rect.x = 0;
			(*PowerUp).Rect.y = 0;
			(*PowerUp).Rect.width = 0;
			(*PowerUp).Rect.height = 0;
		}
		if ((*PowerUp).PowerUpType == "ForceField")
		{
			(*player).ForceFieldTimer = 0;
			(*PowerUp).Rect.x = 0;
			(*PowerUp).Rect.y = 0;
			(*PowerUp).Rect.width = 0;
			(*PowerUp).Rect.height = 0;
		}
	}
}


//Create an object that can deflect bullets by rotating them and giving them a different
//Vector2 to move from
void RenderObject(Bullet *Arr, float Rotation, Rectangle Rect)
{
	DrawRectanglePro(Rect, { Rect.x, Rect.y }, Rotation, SKYBLUE);

}



void SaveGame(Player player)
{
	fstream file("Save.txt", ios::out);
	if (file.is_open())
	{
		file << player.HighScore << endl;
		file << player.Shoot << endl;
		file.close();
	}
	
}
void LoadGame(Player *player)
{
	fstream file("Save.txt", ios::in);
	if (file.is_open())
	{
		string line;
		getline(file, line);
		if(line.length() > 0)
			(*player).HighScore = stoi(line);
		getline(file, line);
		if (line.length() > 0)
			(*player).Shoot = line;
		file.close();
	}
	
}
