#pragma once
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "GLTexture.h"
#include <string>

//Definir distintos sprites para hijos de Agent
#include "ResourceManager.h"

using namespace std;

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

enum class AgentType {
	PLAYER,
	ZOMBIE,
	HUMAN
};

class Zombie;
class Human;

class Agent
{
protected:
	//variables para la animación del sprite
	int curFrame, valDirec, animSpeed;
	SpriteBatch spritebatch;

	AgentType type;
	glm::vec2 position;
	float speed;
	Color color;
	void checkTilePosition(const vector<string>& levelData,
		vector<glm::vec2>& collideTilePosition, float x, float y);
	void collideWithTile(glm::vec2 tilePos);
public:
	Agent();
	virtual ~Agent();
	glm::vec2 getPosition()const { return position; }
	virtual void update(vector<string>& levelData,
		vector<Human*>& humans,
		vector<Zombie*>& zombies);

	virtual void draw(SpriteBatch& spritebatch);
	void setPosition(glm::vec2 newPos) { position = newPos; }

	bool collideWithLevel(const vector<string>levelData);
	bool collideWithAgent(Agent* agent);
};

