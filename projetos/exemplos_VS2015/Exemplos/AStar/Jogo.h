#pragma once
#include "libUnicornio.h"
#include "Mapa.h"

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

	Mapa mapa;
};

