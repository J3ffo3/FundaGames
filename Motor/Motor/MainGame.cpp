#include "MainGame.h"
#include "Sprite.h"

MainGame::MainGame()
{
	window = nullptr;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
	// Agregar las rutas de archivo de las imágenes disponibles al vector
	//Imagenes Mario y amigos
	imagePaths.push_back("Images/paperMarioJumpPose.png");
	imagePaths.push_back("Images/paperMarioHammer.png");
	imagePaths.push_back("Images/paperMario&Olivia.png");
	imagePaths.push_back("Images/paperMarioLuigi.png");
	imagePaths.push_back("Images/paperMarioPeach.png");
	imagePaths.push_back("Images/paperMarioBowsyJr.png");
	//Imagenes Toads
	imagePaths.push_back("Images/paperMarioRedToad.png");
	imagePaths.push_back("Images/paperMarioRelaxedBlueToad.png");
	imagePaths.push_back("Images/paperMarioBlueToad.png");
}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Ventana_del_TA02", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	// ES VALIDAR SI HUBO UN ERROR
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		//FALTA VALIDAR EL ESTADO DE GLEW
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	initShaders();
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", 
		"Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();
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

void MainGame::run()
{
	init();
	//La primer imagen hecha en clase se agrega al inicio del vector de sprites para que se muestre primero
	sprites.push_back(Sprite());
	sprites.back().init(0, -1, 1, 1, "Images/paperMarioFightPose.png");
	//Aqui ya se agregan las nuevas imagenes
	update();

}

void MainGame::update()
{
	static int frameCount = 0;
	static const int FRAME_INTERVAL = 4600; // Ajusta este valor según la velocidad deseada
	// Bucle principal del juego
	while (gameState != GameState::EXIT) {
		processInput();
		draw();
		frameCount++;
		if (frameCount == FRAME_INTERVAL) {
			frameCount = 0;
			// Agrega un nuevo sprite aleatorio a la ventana
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

	// Generamos un índice aleatorio para seleccionar una imagen aleatoria de la lista de rutas de las imagenes
	int randomIndex = rand() % imagePaths.size();

	// Obtenemos la ruta de archivo de una imagen aleatoria
	string randomImagePath = imagePaths[randomIndex];

	// Creamos y agregamos un nuevo sprite usando la imagen aleatoria
	sprites.push_back(Sprite()); // Agrega un nuevo sprite al vector de sprites
	sprites.back().init(randomX, randomY, randomWidth, randomHeight, randomImagePath); // Inicializa el último sprite agregado
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << "Posicion en X: " << event.motion.x <<
					"Posicion Y: " << event.motion.y << endl;
			break;
		}
	}
}

MainGame::~MainGame()
{

}
