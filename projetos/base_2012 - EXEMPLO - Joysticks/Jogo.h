#pragma once
#include "Player.h"

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();

private:
	SpriteSheet sheets[MAXIMO_DE_PLAYERS];
	Player players[MAXIMO_DE_PLAYERS];
};

