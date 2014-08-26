#include "Personagem.h"


Personagem::Personagem()
{
	vel = 2.5;
	x = 0;
	y = 0;
}

Personagem::~Personagem()
{
}

void Personagem::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Personagem::mover(float horizontal, float vertical)
{
	x += vel*horizontal;
	y += vel*vertical;
}

void Personagem::setSpriteSheet(SpriteSheet* spritesheet)
{
	sprite.setSpriteSheet(spritesheet);
}

void Personagem::desenhar()
{
	sprite.desenhar(x, y);
}