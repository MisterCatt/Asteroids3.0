#pragma once
#include "GameObject.h"
class UFO : public GameObject
{
public:
	UFO(Screen& screen);
	~UFO();

	void Update();
	void Render();

	float getAngle() override;

private:
	void Move();

	void NewAngle();

	int ufoAngleTimer, angleTimerBase;

	int deadTimer, baseDeadTimer;
};

