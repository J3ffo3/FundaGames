#include "Human.h"
#include "ResourceManager.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

Human::Human()
{

}

Human::~Human()
{
}

void Human::init(float speed, glm::vec2 position)
{
	this->speed = speed;
	//color.set(185, 0, 0, 255);
	color.set(255, 255, 255, 255);
	this->position = position;

	srand(time(NULL));
	curFrame = rand() % 4;
	valDirec = 1;
	animSpeed = 0;

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);
	direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	type = AgentType::HUMAN;
	if (direction.length() == 0) {
		direction = glm::vec2(1.0f, 1.0f);
	}
	//direction = glm::vec2(direction);
}

void Human::update(vector<string>& levelData, vector<Human*>& humans, vector<Zombie*>& zombies)
{
	std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float>randRotate(-40.0f, 40.0f);
	position += direction * speed;
	if (collideWithLevel(levelData)) {
		direction = glm::rotate(direction, randRotate(randomEngine));
	}

	if (direction.x * speed < 0) {
		valDirec = -1;
	}
	//Condicional si el movimiento es positivo(a la derecha) cambiar direccion vertical del frame

	if (direction.x * speed >= 0) {
		valDirec = 1;
	}

	//reducir tiempo del frame de animacion
	animSpeed++;
	if (animSpeed == 8) {
		curFrame = (curFrame + 1) % 4;
		animSpeed = 0;
	}

}