#pragma once
#include "Screen.h"
#include "Player.h"
#include "Asteroids.h"
#include <deque>
#include<cmath>
#include <iostream>
#include "Bullet.h"
#include "UFO.h"

class Game
{
public:
	Game(Screen& screen);
	~Game();

	void run();

private:

	void Update();
	void Render();

	void WorldWrap(GameObject& obj);

	void OnCollision(GameObject& obj1, GameObject& obj2);

	void PlayerUpdate();
	void BulletUpdate();
	void AsteroidUpdate();
	void UFOUpdate();

	void DeleteAll();

	Screen& m_screen;

	Player* m_player;
	std::deque<Asteroids*> asteroidsArray;
	std::deque<Bullet*> bulletArray;
	std::deque<Bullet*> UFOBulletArray;
	UFO* ufo;

	Sound boom;
	Sprite playerLifeSprite;

	bool deleted;

	int test;

	int shotTimer;

	bool tempDead;
	int deadTimer;
	int lives;

	int score;

	int bigAsteroidScore, mediumAsteroidScore, smallAsteroidScore, UFOScore;

	int UFOBulletTimer, UFOBaseulletTimer;
};

