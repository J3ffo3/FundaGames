#pragma once
#include "Agent.h"
#include "Player.h"
class Zombie :
    public Agent
{
private:
    glm::vec2 direction;
    // Funci�n privada para corregir la posici�n si hay superposici�n
    void correctPosition(vector<Zombie*>& zombies);

public:
    Zombie();
    ~Zombie();
    void init(float speed, glm::vec2 position);
    void update(vector<string>& levelData,
        vector<Human*>& humans,
        vector<Zombie*>& zombies, Player* player);
};

