#include "Zombie.h"
#include <random>
#include <ctime>
#include<glm/gtx/constants.hpp>
#include<glm/gtx/rotate_vector.hpp>


void Zombie::correctPosition(vector<Zombie*>& zombies)
{
	const float MIN_DISTANCE = AGENT_WIDTH;

	for (size_t i = 0; i < zombies.size(); ++i) {
		if (zombies[i] != this) { // No comparamos el zombie consigo mismo
			glm::vec2 distVec = position - zombies[i]->getPosition();
			float distance = glm::length(distVec);

			if (distance < MIN_DISTANCE) {
				glm::vec2 correction = glm::normalize(distVec) * (MIN_DISTANCE - distance);
				position += correction / 2.0f;
				zombies[i]->position -= correction / 2.0f;
			}
		}
	}
}

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 position)
{
	this->speed = speed;
	color.set(0, 255, 1, 255);
	this->position = position;

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);
	direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (direction.length() == 0) {
		direction = glm::vec2(1.0f, 1.0f);
	}
}

void Zombie::update(vector<string>& levelData, vector<Human*>& humans, vector<Zombie*>& zombies, Player* player)
{
	direction = glm::normalize(player->getPlayerPosition() - position);
	position += direction * speed;
	if (collideWithLevel(levelData)) {
		std::mt19937 randomEngine(time(nullptr));
		std::uniform_real_distribution<float>randRotate(-40.0f, 40.0f);
		direction = glm::rotate(direction, randRotate(randomEngine));
	}
	correctPosition(zombies);
}
