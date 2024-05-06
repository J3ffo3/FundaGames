#pragma once
#include <GL/glew.h>
#include <string>
#include "GLTexture.h"
using namespace std;

class Sprite
{
private:
	float x, y;
	int width, height;
	float vertexData;
	GLuint vboID;
	GLTexture texture;
public:
	Sprite();
	~Sprite();
	void init(float x, float y, float width, 
		float height, string texturePath);
	void draw();
};