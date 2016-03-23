#pragma once
#include "libUnicornio.h"

class Personagem
{
public:
	Personagem();
	~Personagem();

	void setPos(int x, int y);
	void setSpriteSheet(string spritesheet);

	void animar();

	//	os parametros variam de -1.0 à +1.0
	void mover(float horizontal, float vertical);

	void desenhar();

protected:
	Sprite sprite;
	float x, y;
	float vel;
};

