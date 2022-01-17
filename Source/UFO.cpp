#include "UFO.h"
UFO::UFO(Screen& screen) : GameObject(screen)
{
	m_name = "UFO";

	m_sprite = m_screen.LoadSprite("assets/UFO.png");

	m_angle = rand() % 180;

	m_speed = 3;

	ufoAngleTimer = angleTimerBase = 240;
	deadTimer = baseDeadTimer = 520;
	
	popThis = true;
}

UFO::~UFO()
{
}

void UFO::Move() {
	float x_vec = (float)sin(m_angle * 3.14159265358979323846 / -180.0f);
	float y_vec = (float)cos(m_angle * 3.14159265358979323846 / 180.0f);

	float magnitude = sqrt(x_vec * x_vec + y_vec * y_vec);

	setX(m_pos.x + x_vec / magnitude * m_speed);
	setY(m_pos.y + y_vec / magnitude * m_speed);
}

void UFO::Update() {
	if (!PopThis()) {
		UppdateCoordinates();

		if (ufoAngleTimer == 0) {
			NewAngle();
			ufoAngleTimer = angleTimerBase;
		}

		Move();

		ufoAngleTimer--;
	}
	else {
		setX(m_screen.GetWindowWidth()*6);
		setY(m_screen.GetWindowHeight()*6);

		deadTimer--;
		if (deadTimer == 0) {
			setX(rand() % m_screen.GetWindowWidth());
			setY(rand() % m_screen.GetWindowHeight());

			m_angle = rand() % 180;

			deadTimer = baseDeadTimer;

			setPop(false);
		}
	}
}

void UFO::Render() {
	if(!PopThis())
	m_screen.DrawSprite(m_sprite);
}

void UFO::NewAngle() {
	m_angle = rand() % 180;
}

float UFO::getAngle() {
	return m_angle;
}