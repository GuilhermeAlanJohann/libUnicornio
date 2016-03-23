#pragma once
#include "libUnicornio.h"
#include "InputTexto.h"

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

	InputTexto input;
};

