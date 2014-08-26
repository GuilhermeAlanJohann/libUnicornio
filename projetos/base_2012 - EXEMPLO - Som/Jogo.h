#pragma once
#include "TocadorDeSom.h"

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();

private:
	TocadorDeSom tocador;
};

