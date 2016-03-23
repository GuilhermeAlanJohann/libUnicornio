#ifndef JOGO_H
#define JOGO_H

#include "libUnicornio.h"
#include "Ambiente.h"

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

	Ambiente ambiente;
	
};

#endif