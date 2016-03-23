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
	void desenharInstrucoes();
	Player players[MAXIMO_DE_PLAYERS];
};

