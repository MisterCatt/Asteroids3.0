#pragma once
#include "GameObject.h"
class Asteroids : public GameObject
{
public:
	Asteroids(Screen& screen, int size, Vector2 pos, float angle);
	~Asteroids();

	void Update();
	void Render();

	float getRadius() override;

	int getSize();

private:

	void Move();

	int m_size;

};

