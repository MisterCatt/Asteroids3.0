#pragma once
#include "Screen.h"

class GameObject
{
public:

	GameObject(Screen& screen);
	~GameObject();

	virtual Vector2 getVector2();
	virtual std::string getName();

	virtual float getRadius();
	virtual float getAngle();

	virtual void setX(float x);
	virtual void setY(float y);

	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void UppdateCoordinates();

	virtual bool PopThis();
	virtual void setPop(bool x);

	virtual void setName(std::string name);

protected:

	Screen& m_screen;
	Sprite m_sprite;

	Vector2 m_pos;

	float m_angle;

	float m_speed;

	std::string m_name;

	bool popThis;
};
