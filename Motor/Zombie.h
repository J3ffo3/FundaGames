#pragma once
#include "Agent.h"
#include "Player.h"
class Zombie :
    public Agent
{
private:
    glm::vec2 direction;
    // Función privada para corregir la posición si hay superposición
    void correctPosition(vector<Zombie*>& zombies);

public:
    Zombie();
    ~Zombie();
    void init(float speed, glm::vec2 position);
    void update(vector<string>& levelData,
        vector<Human*>& humans,
        vector<Zombie*>& zombies, Player* player);
};

