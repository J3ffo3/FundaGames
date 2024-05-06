#pragma once
#include <SDL/SDL.h>
#include<GL/eglew.h>
#include <iostream>
#include "Sprite.h"
#include "GLS_Program.h"
#include <vector>

using namespace std;

enum class GameState {
	PLAY, EXIT
};

class MainGame
{
private:
	vector<Sprite> sprites;
	vector<string> imagePaths; //Vector para almacenar las rutas de las diferentes imagenes que se van a generar aleatoriamente en la ventana
	Sprite sprite;
	int width;
	int height;
	SDL_Window* window;
	void init();
	void processInput();
	GLS_Program program;
	void initShaders();
	float time = 0;
public:
	MainGame();
	~MainGame();
	GameState gameState;
	void run();
	void draw();
	void update();
	void addRandomSprite();
};

