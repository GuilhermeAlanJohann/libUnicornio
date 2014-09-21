#pragma once
#include "libUnicornio.h"

enum PersonagemAnim
{
	PARADO,
	CAMINHANDO_BAIXO,
	CAMINHANDO_ESQ,
	CAMINHANDO_DIR,
	CAMINHANDO_CIMA
};

class Personagem
{
public:
	Personagem();
	~Personagem();

	void setPos(int x, int y);
	void setVel(float vel);
	void setSpriteSheet(string spritesheet);

	void moverDir();
	void moverEsq();
	void moverCima();
	void moverBaixo();

	void ficarParado();

	void animar();
	void desenhar();

protected:
	Sprite sprite;
	float x, y;
	float vel;
};

