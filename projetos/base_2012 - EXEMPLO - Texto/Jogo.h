#pragma once
#include "libUnicornio.h"

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();

private:
	Fonte fonte;
	Fonte fonteMaior;
	Texto texto;
	Texto textoMaior;
};

