#include "Tiro.h"


Tiro::Tiro()
{
	vel = 0.8;
}

Tiro::~Tiro()
{
}

void Tiro::setSpriteSheet(string sheet)
{
	spr.setSpriteSheet(sheet);
}

void Tiro::setPos(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Tiro::setEscala(float x, float y)
{
	spr.setEscala(x, y);
}

Sprite Tiro::getSprite()
{
	return spr;
}

float Tiro::getPosX()
{
	return x;
}

float Tiro::getPosY()
{
	return y;
}

float Tiro::getRot()
{
	return 0;
}

void Tiro::atualizar()
{
	spr.avancarAnimacao();
	y += vel;
}

void Tiro::desenhar()
{
	spr.desenhar(x, y);
}