#include "Zombie.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>
#include "Human.h"
#include "ResourceManager.h"

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 position)
{
	srand(time(NULL));

	curFrame = rand() % 6;
	valDirec = 1;
	animSpeed = 0;

	this->speed = speed;
	//color.set(0, 255, 0, 255);
	color.set(255, 255, 255, 255);
	this->position = position;
	type = AgentType::ZOMBIE;

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);
	direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (direction.length() == 0) {
		direction = glm::vec2(1.0f, 1.0f);
	}
}

void Zombie::update(vector<string>& levelData,
	vector<Human*>& humans, vector<Zombie*>& zombies)
{
	collideWithLevel(levelData);
	type = AgentType::ZOMBIE;
	Human* closeHuman = getNearestHuman(humans);
	if (closeHuman != nullptr) {
		direction = glm::normalize(
			closeHuman->getPosition() - position
		);
		position += direction * speed;

		if ((direction.x * speed) < 0) {
			valDirec = -1;
		}
		if ((direction.x * speed) >= 0) {
			valDirec = 1;
		}
	}
	

	animSpeed++;
	if (animSpeed == 8) {
		curFrame = (curFrame + 1) % 6;
		animSpeed = 0;
	}

	
}


Human* Zombie::getNearestHuman(vector<Human*>& humans)
{
	Human* closeHuman = nullptr;
	float smallestDistance = 888888888.0f;
	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 dist = humans[i]->getPosition() - position;
		float distance = glm::length(dist);
		if (distance < smallestDistance) {
			smallestDistance = distance;
			closeHuman = humans[i];
		}
	}
	return closeHuman;
}
