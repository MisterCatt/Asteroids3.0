#include "Asteroids.h"

Asteroids::Asteroids(Screen& screen, int size = 1, Vector2 pos = Vector2(0,0), float angle = rand() % 180) : GameObject(screen)
{
	if(size == 1)
	m_sprite = m_screen.LoadSprite("assets/Asteroid1.png");
	else if(size == 2)
	m_sprite = m_screen.LoadSprite("assets/AsteroidMedium.png");
	else
	m_sprite = m_screen.LoadSprite("assets/AsteroidMini.png");

	m_pos = pos;

	m_angle = angle;
	m_speed = 3;

	m_size = size;

	m_name = "Asteroid";
}

Asteroids::~Asteroids()
{
}

void Asteroids::Update() {
	UppdateCoordinates();
	Move();
}

void Asteroids::Render() {
	m_screen.DrawSprite(m_sprite);
}

void Asteroids::Move() {
	float x_vec = (float)sin(m_angle * 3.14159265358979323846 / -180.0f);
	float y_vec = (float)cos(m_angle * 3.14159265358979323846 / 180.0f);

	float magnitude = sqrt(x_vec * x_vec + y_vec * y_vec);

	setX(m_pos.x + x_vec / magnitude * m_speed);
	setY(m_pos.y + y_vec / magnitude * m_speed);
}

float Asteroids::getRadius() {
	return m_sprite.texture.width / 2;
}

int Asteroids::getSize() {
	return m_size;
}