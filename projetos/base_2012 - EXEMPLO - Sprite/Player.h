#pragma once
#include "Personagem.h"

class Player
{
public:
	Player();
	~Player();

	void inicializar();
	void finalizar();

	void atualizar();
	void desenhar();

private:
	Personagem per;				//	personagem que representa o player no jogo
	SpriteSheet spritesheet;	//	spritesheet do personagem
};

