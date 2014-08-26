#pragma once
#include "libUnicornio.h"

class TocadorDeSom
{
public:
	TocadorDeSom();
	~TocadorDeSom();

	void inicializar();
	void finalizar();

	void atualizar();
	void desenharInstrucoes();

private:
	Som som;
};

