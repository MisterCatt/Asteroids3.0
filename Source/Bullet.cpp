#include "Bullet.h"

Bullet::Bullet(Screen& screen, float angle, Vector2 pos) : GameObject(screen)
{
	m_sprite = m_screen.LoadSprite("assets/bullet.png");

	m_angle = angle;
	m_speed = 5;

	bulletTimer = 120;

	m_name = "Bullet";

	setX(pos.x);
	setY(pos.y);
}

Bullet::~Bullet()
{
}

void Bullet::Update() {
	UppdateCoordinates();

	Move();

	if(bulletTimer >= 0)
	bulletTimer--;
}

void Bullet::Render() {
	m_screen.DrawSprite(m_sprite);
}

void Bullet::Move() {
	float x_vec = (float)sin(m_angle * 3.14159265358979323846 / -180.0f);
	float y_vec = (float)cos(m_angle * 3.14159265358979323846 / 180.0f);

	float magnitude = sqrt(x_vec * x_vec + y_vec * y_vec);

	setX(m_pos.x + x_vec / magnitude * m_speed);
	setY(m_pos.y + y_vec / magnitude * m_speed);
}

bool Bullet::RemoveBullet() {
	return bulletTimer == 0;
}