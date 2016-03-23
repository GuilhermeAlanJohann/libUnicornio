#include "Personagem.h"


Personagem::Personagem()
{
	vel = 2.5;
	x = 0;
	y = 0;
	sprite.setEscala(0.2, 0.2);
}

Personagem::~Personagem()
{
}

void Personagem::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Personagem::animar()
{
	sprite.avancarAnimacao();
}

void Personagem::mover(float horizontal, float vertical)
{
	x += vel*horizontal;
	y += vel*vertical;

	if (horizontal > 0)
	{
		sprite.setAnimacao(1);
		sprite.setInverterX(false);
	}
	else if (horizontal < 0)
	{
		sprite.setAnimacao(1);
		sprite.setInverterX(true);
	}
	else if (vertical != 0)
	{
		sprite.setAnimacao(1);
	}
	else
	{
		sprite.setAnimacao(0);
	}
}

void Personagem::setSpriteSheet(string spritesheet)
{
	sprite.setSpriteSheet(spritesheet);
}

void Personagem::desenhar()
{
	sprite.desenhar(x, y);
}