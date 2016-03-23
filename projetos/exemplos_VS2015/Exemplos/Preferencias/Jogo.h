#pragma once
#include "libUnicornio.h"
#include "DadosDoJogador.h"

#define NUM_ACHIVEMENTS 3

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();

private:
	void atualizar();
	void desenharInstrucoes();
	void desenhar();

	Preferencias prefs;
	DadosDoJogador dados;
};

