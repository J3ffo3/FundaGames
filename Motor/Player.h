#pragma once
#include "Agent.h"
#include "InputManager.h"
#include "algorithm"

enum direction {
    MoveU,
    MoveD,
    MoveL,
    MoveR
};

class Player :
    public Agent
{
private:
    InputManager* inputmanager;
    int direction;
   
public:

    Player();
    ~Player();
    void init(float speed, glm::vec2 position, InputManager* inputManager);
    void update(vector<string>& levelData,
        vector<Human*>& humans,
        vector<Zombie*>& zombies, AgentType type);
    glm::vec2 getDirection();
  
};

