#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(Screen& screen, float angle, Vector2 pos);
	~Bullet();

	void Update();
	void Render();

	bool RemoveBullet();

private:

	void Move();

	int bulletTimer;

};

