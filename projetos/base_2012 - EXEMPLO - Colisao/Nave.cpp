#include "Nave.h"


Nave::Nave()
{
}

Nave::~Nave()
{
}

void Nave::setSpriteSheet(SpriteSheet* sheet)
{
	spr.setSpriteSheet(sheet);
}

void Nave::setPos(float x, float y)
{
	this->x = x;
	this->y = y;
}

Sprite* Nave::getSprite()
{
	return &spr;
}

float Nave::getPosX()
{
	return x;
}

float Nave::getPosY()
{
	return y;
}

float Nave::getRot()
{
	return 0;
}

void Nave::desenhar()
{
	spr.desenhar(x, y);
}