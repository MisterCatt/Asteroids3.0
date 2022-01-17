#pragma once
#include "Game.h"

Game::Game(Screen& screen) : m_screen(screen)
{
	m_player = new Player(m_screen);
	boom = m_screen.LoadSound("assets/boom.ogg");
	playerLifeSprite = m_screen.LoadSprite("assets/player.png");

	asteroidsArray.push_back(new Asteroids(m_screen, 1,  Vector2(rand()% m_screen.GetWindowWidth(), rand()%m_screen.GetWindowHeight()), rand()%180));
	asteroidsArray.push_back(new Asteroids(m_screen, 1,  Vector2(rand()% m_screen.GetWindowWidth(), rand()%m_screen.GetWindowHeight()), rand()%180));
	asteroidsArray.push_back(new Asteroids(m_screen, 1,  Vector2(rand()% m_screen.GetWindowWidth(), rand()%m_screen.GetWindowHeight()), rand()%180));

	ufo = new UFO(m_screen);

	test = 0;
	shotTimer = 30;

	lives = 3;
	tempDead = false;
	deadTimer = 160;

	score = 0;

	bigAsteroidScore = 20;
	mediumAsteroidScore = 70;
	smallAsteroidScore = 140;
	UFOScore = 300;

	UFOBulletTimer = UFOBaseulletTimer = 120;

	deleted = false;
}

Game::~Game()
{
}

void Game::Update() {
	if (lives > 0) {
		if (!tempDead)
			PlayerUpdate();
		else {
			if (deadTimer == 0) {
				tempDead = false;
				std::cout << "Alive" << std::endl;
				deadTimer = 160;
			}
			deadTimer--;
		}
	

	BulletUpdate();

	AsteroidUpdate();

	UFOUpdate();

	if (asteroidsArray.size() == 0) {
		asteroidsArray.push_back(new Asteroids(m_screen, 1, Vector2(rand() % m_screen.GetWindowWidth(), rand() % m_screen.GetWindowHeight()), rand() % 180));
		asteroidsArray.push_back(new Asteroids(m_screen, 1, Vector2(rand() % m_screen.GetWindowWidth(), rand() % m_screen.GetWindowHeight()), rand() % 180));
		asteroidsArray.push_back(new Asteroids(m_screen, 1, Vector2(rand() % m_screen.GetWindowWidth(), rand() % m_screen.GetWindowHeight()), rand() % 180));
	}

	}
	else {
		if(!deleted)
		DeleteAll();
	}
}

void Game::Render() {
	if (lives > 0) {
		{
			playerLifeSprite.position.x = m_screen.GetWindowWidth() / 6 + 100;
			playerLifeSprite.position.y = m_screen.GetWindowHeight() / 6;
			playerLifeSprite.scale = 0.5;
			int spacing = 15;
			for (int i = 0; i < lives; i++) {
				m_screen.DrawSprite(playerLifeSprite);
				playerLifeSprite.position.x += spacing;
			}
			
			m_screen.DrawText(m_screen.GetWindowWidth() / 6, m_screen.GetWindowHeight() / 6, { 255,255,255 }, "Lives: ");
			m_screen.DrawText(m_screen.GetWindowWidth() / 6, m_screen.GetWindowHeight() / 8, { 255,255,255 }, "Score: " + std::to_string(score));
		}
		if (!tempDead)
			m_player->Render();

		for (Bullet* b : bulletArray) {
			b->Render();
		}

		for (Bullet* b : UFOBulletArray) {
			b->Render();
		}

		for (Asteroids* a : asteroidsArray) {
			a->Render();
		}

		ufo->Render();
	}
	else {
		m_screen.DrawText(m_screen.GetWindowWidth() / 2 - 100, m_screen.GetWindowHeight() / 2.1, {255,255,255}, "You are dead!");
		m_screen.DrawText(m_screen.GetWindowWidth() / 2 - 100, m_screen.GetWindowHeight() / 2, {255,255,255}, "Final score: " + std::to_string(score));
	}
}

void Game::run() {
	Render();
	Update();
}

void Game::WorldWrap(GameObject& obj) {
	if (obj.getVector2().x > m_screen.GetWindowWidth()) {
		obj.setX(0);
	}
	if (obj.getVector2().y > m_screen.GetWindowHeight()) {
		obj.setY(0);
	}
	if (obj.getVector2().x < 0) {
		obj.setX(m_screen.GetWindowWidth());
	}
	if (obj.getVector2().y < 0) {
		obj.setY(m_screen.GetWindowHeight());
	}

	
}
//help from https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
void Game::OnCollision(GameObject& obj1, GameObject& obj2) {
	float o1x = (obj1.getVector2().x + obj1.getRadius()) - (obj2.getVector2().x + obj2.getRadius());
	float o2y = (obj1.getVector2().y + obj1.getRadius()) - (obj2.getVector2().y + obj2.getRadius());
	float distance = std::sqrt(o1x * o1x + o2y * o2y);

	if (distance < obj1.getRadius() + obj2.getRadius()) {
		if (obj2.getName() == "Player") {
			if (!tempDead) {
				m_screen.PlaySound(boom);
				tempDead = true;
				delete m_player;
				lives--;
				m_player = new Player(m_screen);
				std::cout << "Dead: " << test++ << std::endl;
			}
		}
		else if (obj2.getName() == "Bullet") {
			m_screen.PlaySound(boom);
			std::cout << "Destroy: " << test++ << std::endl;

			obj1.setPop(true);
			obj2.setPop(true);

			if (obj1.getName() == "UFO") {
				score += UFOScore;
			}

		}
	}
}

void Game::PlayerUpdate() {
	m_player->Update();

	if (m_player->HasShot()) {
		bulletArray.push_back(new Bullet(m_screen, m_player->getAngle(), m_player->getVector2()));
	}
	m_player->ResetShot();
	WorldWrap(*m_player);
}

void Game::BulletUpdate() {
	for (Bullet* b : bulletArray) {
		b->Update();
		WorldWrap(*b);

		if (b->RemoveBullet()) {
			bulletArray.pop_front();
		}

		OnCollision(*ufo, *b);
	}

	for (int i = 0; i < bulletArray.size(); i++) {
		if (bulletArray.at(i)->PopThis()) {
			bulletArray.erase(bulletArray.begin() + i);
		}
	}

	//UFO Bullets
	for (Bullet* b : UFOBulletArray) {
		b->Update();
		if(!ufo->PopThis())
		WorldWrap(*b);
		OnCollision(*b, *m_player);

		if (b->RemoveBullet()) {
			UFOBulletArray.pop_front();
		}
	}

	for (int i = 0; i < UFOBulletArray.size(); i++) {
		if (UFOBulletArray.at(i)->PopThis()) {
			UFOBulletArray.erase(UFOBulletArray.begin() + i);
		}
	}
}

void Game::AsteroidUpdate() {
	for (Asteroids* a : asteroidsArray) {
		a->Update();
		WorldWrap(*a);
		OnCollision(*a, *m_player);
		for(Bullet* b : bulletArray)
		OnCollision(*a, *b);
	}

	for (int i = 0; i < asteroidsArray.size(); i++) {
		if (asteroidsArray.at(i)->PopThis()) {
			if (asteroidsArray.at(i)->getSize() == 1) {
				score += bigAsteroidScore;
				asteroidsArray.push_back(new Asteroids(m_screen,2, asteroidsArray.at(i)->getVector2(), asteroidsArray.at(i)->getAngle()+40));
				asteroidsArray.push_back(new Asteroids(m_screen,2, asteroidsArray.at(i)->getVector2(), asteroidsArray.at(i)->getAngle()-40));
			}
			else if (asteroidsArray.at(i)->getSize() == 2) {
				score += mediumAsteroidScore;
				asteroidsArray.push_back(new Asteroids(m_screen, 3, asteroidsArray.at(i)->getVector2(), asteroidsArray.at(i)->getAngle() + 40));
				asteroidsArray.push_back(new Asteroids(m_screen, 3, asteroidsArray.at(i)->getVector2(), asteroidsArray.at(i)->getAngle() - 40));
				asteroidsArray.push_back(new Asteroids(m_screen, 3, asteroidsArray.at(i)->getVector2(), asteroidsArray.at(i)->getAngle() + 20));
				asteroidsArray.push_back(new Asteroids(m_screen, 3, asteroidsArray.at(i)->getVector2(), asteroidsArray.at(i)->getAngle() - 20));
			}
			else {
				score += smallAsteroidScore;
			}
			asteroidsArray.erase(asteroidsArray.begin() + i);
		}
	}
}

void Game::UFOUpdate() {
	ufo->Update();
	WorldWrap(*ufo);

	OnCollision(*ufo, *m_player);

	if (UFOBulletTimer == 0) {
		UFOBulletArray.push_back(new Bullet(m_screen, rand()% 180, ufo->getVector2()));
		UFOBulletTimer = 120;
	}
	UFOBulletTimer--;
}

void Game::DeleteAll() {
	if (!asteroidsArray.empty()) {
		for (Asteroids* a : asteroidsArray) {
			asteroidsArray.pop_back();
		}
	}

	delete m_player;
	m_player = nullptr;

	delete ufo;
	ufo = nullptr;

	deleted = true;
}