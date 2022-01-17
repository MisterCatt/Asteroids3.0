#include "GameObject.h"

GameObject::GameObject(Screen& screen) : m_screen(screen) {
	m_speed = m_angle = 0.0f;
	popThis = false;
}

GameObject::~GameObject() {

}

Vector2 GameObject::getVector2() {
	return m_pos;
}


void GameObject::setX(float x) {
	m_pos.x = x;
}

void GameObject::setY(float y) {
	m_pos.y = y;
}

void GameObject::UppdateCoordinates() {
	m_sprite.position.x = m_pos.x;
	m_sprite.position.y = m_pos.y;
}

float GameObject::getRadius() {
	return m_sprite.texture.width;
}

float GameObject::getAngle() {
	return m_sprite.angle;
}

std::string GameObject::getName() {
	return m_name;
}

bool GameObject::PopThis() {
	return popThis;
}

void GameObject::setPop(bool x) {
	popThis = x;
}

void GameObject::setName(std::string name) {
	m_name = name;
}