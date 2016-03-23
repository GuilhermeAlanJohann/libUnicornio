#pragma once
#include "libUnicornio.h"

class Nave
{
public:
	Nave();
	~Nave();

	void setSpriteSheet(string sheet);
	void setPos(float x, float y);
	void setEscala(float x, float y);

	Sprite getSprite();
	float getPosX();
	float getPosY();
	float getRot();

	void desenhar();

private:
	Sprite spr;
	float x, y;
};

