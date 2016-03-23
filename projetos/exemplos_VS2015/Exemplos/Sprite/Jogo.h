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
	void desenharInstrucoes();

	Personagem per;				//	personagem que representa o player no jogo

};

