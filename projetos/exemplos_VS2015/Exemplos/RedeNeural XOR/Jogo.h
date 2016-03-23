#ifndef JOGO_H
#define JOGO_H

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
	void atualizarInput();
	void atualizar();
	void desenharInstrucoes();

	bool treinando;
	RedeNeural rede;
};

#endif