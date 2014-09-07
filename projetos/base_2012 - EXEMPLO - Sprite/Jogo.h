#pragma once
#include "Personagem.h"

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();

private:
	Personagem per;				//	personagem que representa o player no jogo
	SpriteSheet spritesheet;	//	spritesheet do personagem
};

