#include "Nave.h"


Nave::Nave()
{
}

Nave::~Nave()
{
}

void Nave::setSpriteSheet(string sheet)
{
	spr.setSpriteSheet(sheet);
}

void Nave::setPos(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Nave::setEscala(float x, float y)
{
	spr.setEscala(x, y);
}

Sprite Nave::getSprite()
{
	return spr;
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