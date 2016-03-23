#pragma once
#include "libUnicornio.h"
#include "Passaro.h"

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

	Passaro passaro;
};

