#include "Player.h"
#include <SDL/SDL.h>
#include <random>
#include <ctime>
#include "ResourceManager.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(float speed, glm::vec2 position, InputManager* inputManager)
{
	srand(time(NULL));

	curFrame = rand() % 7;
	valDirec = 1;
	animSpeed = 0;

	type = AgentType::PLAYER;
	this->speed = speed;
	this->position = position;
	this->inputmanager = inputManager;
	//color.set(0, 0, 185, 255);
	color.set(255, 255, 255, 255);
}

void Player::update(vector<string>& levelData, vector<Human*>& humans, vector<Zombie*>& zombies, AgentType type)
{
	type = AgentType::PLAYER;
	if (inputmanager->isKeyDown(SDLK_w)) {
		position.y += speed;
		//sprite->Play("Move Up");
		direction = MoveU;
	}
	if (inputmanager->isKeyDown(SDLK_s)) {
		position.y -= speed;
		//sprite->Play("Move Down");
		direction = MoveD;
	}
	if (inputmanager->isKeyDown(SDLK_a)) {
		position.x -= speed;
		//sprite->Play("Move Left");
		direction = MoveL;
		valDirec = -1;
		if (curFrame < 1) {
			curFrame = 7;
		}
		curFrame += valDirec;

		animSpeed++;
		if (animSpeed == 8) {
			curFrame = (curFrame + 1) % 7;
			animSpeed = 0;
		}
	}
	if (inputmanager->isKeyDown(SDLK_d)) {
		position.x += speed;
		//sprite->Play("Move Right");
		valDirec = 1;
		direction = MoveR;
		if (curFrame > 7) {
			curFrame = 1;
		}
		curFrame += valDirec;
		animSpeed++;
		if (animSpeed == 8) {
			curFrame = (curFrame + 1) % 7;
			animSpeed = 0;
		}
	}
	collideWithLevel(levelData);
}

glm::vec2 Player::getDirection()
{
	switch (direction) {

	case MoveU:
		return glm::vec2(0, 1);
		break;
	case MoveD:
		return glm::vec2(0, -1);
		break;
	case MoveL:
		return glm::vec2(-1, 0);
		break;
	case MoveR:
		return glm::vec2(1, 0);
		break;
	}
}
