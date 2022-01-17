#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(Screen& screen);
	~Player();

	void Update();
	void Render();
	bool HasShot();
	void ResetShot();

private:
	void Input();

	void Move();
	
	bool hasShot;
	int cooldown, tpCooldown, baseCooldownTimer, baseTpCooldownTimer;

	Sound shootSound, tpSound, thrustSound;
};
