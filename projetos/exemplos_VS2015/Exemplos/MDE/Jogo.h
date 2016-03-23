#pragma once
#include "libUnicornio.h"
#include "Agente.h"

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
	Agente agente;
};

