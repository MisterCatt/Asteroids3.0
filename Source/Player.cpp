#pragma once
#include "Player.h"


Player::Player(Screen& screen) : GameObject(screen)
{
	m_sprite = m_screen.LoadSprite("assets/Player.png");
	shootSound = m_screen.LoadSound("assets/shot.ogg");
	tpSound = m_screen.LoadSound("assets/teleport.ogg");
	thrustSound = m_screen.LoadSound("assets/thrust.ogg");

	m_sprite.origin.x = m_sprite.texture.width/2;
	m_sprite.origin.y = m_sprite.texture.height/2;

	setX(m_screen.GetWindowWidth()/2);
	setY(m_screen.GetWindowHeight()/2);

	m_name = "Player";

	hasShot = false;

	cooldown = baseCooldownTimer = 20;
	tpCooldown = baseTpCooldownTimer = 60;
}

Player::~Player()
{

}

void Player::Update() {
	UppdateCoordinates();

	Input();

	Move();

	if (cooldown > 0) {
		cooldown--;
	}
	if (tpCooldown > 0) {
		tpCooldown--;
	}
}

void Player::Render() {
	m_screen.DrawSprite(m_sprite);
}

void Player::Input() {
	if (m_screen.IsKeyDown(Key::Up)) {
		m_screen.PlaySound(thrustSound);
		m_angle = m_sprite.angle;

		if (m_speed < 5) {
			m_speed += 0.2f;
		}
	}
	if (m_screen.IsKeyDown(Key::Left)) {
		m_sprite.angle -= 3;
	}
	if (m_screen.IsKeyDown(Key::Right)) {
		m_sprite.angle += 3;
	}
	if (m_screen.IsKeyDown(Key::Down)) {
		if (m_speed <= 0)
			return;
		m_speed -= 0.2f;
	}
		if (m_screen.IsKeyDown(Key::Space)) {
			if (cooldown == 0) {
				m_screen.PlaySound(shootSound);
				hasShot = true;
				cooldown = baseCooldownTimer;
			}
			
		}
		if (m_screen.IsKeyDown(Key::Q)) {
			if (tpCooldown <= 0) {
				m_screen.PlaySound(tpSound);
				setX(rand() % m_screen.GetWindowWidth());
				setY(rand() % m_screen.GetWindowHeight());
				tpCooldown = baseTpCooldownTimer;
			}
		}
}

void Player::Move() {
	float x_vec = (float)sin(m_angle * 3.14159265358979323846 / -180.0f);
	float y_vec = (float)cos(m_angle * 3.14159265358979323846 / 180.0f);

	float magnitude = sqrt(x_vec * x_vec + y_vec * y_vec);

	setX(m_pos.x + x_vec / magnitude * m_speed);
	setY(m_pos.y + y_vec / magnitude * m_speed);

	if (m_speed > 0) {
		m_speed -= 0.1f;
	}
	if (m_speed < 0)
		m_speed = 0;

}

bool Player::HasShot() {
	return hasShot;
}

void Player::ResetShot() {
	hasShot = false;
}