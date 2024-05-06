#include "MainGame.h"
#include "Sprite.h"
#include <cstdlib> 
#include <ctime>

MainGame::MainGame()
{
	window = NULL;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Ventana_del_TA01", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	//es valida si hubo un error
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		//falta validar el estado del glew
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	initShaders();
}

MainGame::~MainGame()
{


}

void MainGame::run()
{
	init();
	//El primer rectangulo hecho en clase se agrega al inicio del vector de sprites para que se muestre primero
	sprites.push_back(Sprite()); 
	sprites.back().init(-1, -1, 1, 1); 
	//Aqui ya se agregan los nuevos rectangulos
	update();
	
}

void MainGame::draw()
{
	//glClearDepth(1.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.002;
	// Dibuja todos los sprites en el vector
	for (auto& sprite : sprites) {
		sprite.draw();
	}
	program.unuse();
	SDL_GL_SwapWindow(window);

}

void MainGame::update()
{
	static int frameCount = 0;
	static const int FRAME_INTERVAL = 4650; // Ajusta este valor según la velocidad deseada
	// Bucle principal del juego
	while (gameState != GameState::EXIT) {
		draw();
		processInput();
		frameCount++;
		if (frameCount == FRAME_INTERVAL) {
			frameCount = 0;
			// Agrega un nuevo sprite en un lugar aleatorio a la ventana
			addRandomSprite();
		}
	}
}

void MainGame::addRandomSprite()
{
	float randomX = -1.0 + ((float)rand() / RAND_MAX) * 1.0;
	float randomY = -1.0 + ((float)rand() / RAND_MAX) * 1.0;
	float randomWidth = (rand() % 10 + 1) / 10.0;
	float randomHeight = (rand() % 10 + 1) / 10.0;

	sprites.push_back(Sprite()); // Agrega un nuevo sprite al vector de sprites
	sprites.back().init(randomX, randomY, randomWidth, randomHeight); // Inicializa el último sprite agregado
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type) {
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << " Posicion en X " << event.motion.x 
				<< " Posicion en Y " << event.motion.y << endl;
			break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPoistion");
	program.addAtribute("vertexColor");

	program.linkShader();

}
