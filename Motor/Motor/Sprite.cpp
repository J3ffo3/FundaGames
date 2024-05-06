#include "Sprite.h"
#include "Vertex.h"
#include<cstddef>
#include <cstdlib>
#include <ctime> 

Sprite::~Sprite()
{//vertex buffer id
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}
}

void Sprite::init(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}
	
	Vertex vertexData[6];

	//Posiciones
	vertexData[0].setPosition(x + width, y + height);
	vertexData[1].setPosition(x , y + height);
	vertexData[2].setPosition(x, y );
	vertexData[3].setPosition(x, y );
	vertexData[4].setPosition(x + width, y );
	vertexData[5].setPosition(x + width, y + height);

	//Color
	int randomR = (rand() % 256);
	int randomG = (rand() % 256);
	int randomB = (rand() % 256);
	int randomA = (rand() % 256);

	for (int i = 0; i < 6; i++)
	{
		//	red green blue alpha
		vertexData[i].setColor(255, 0, 0, 255);
	}
	vertexData[1].setColor(randomR, randomG, randomB, randomA);
	vertexData[4].setColor(randomR, randomG, randomB, randomA);


	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData , GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

Sprite::Sprite()
{
}
