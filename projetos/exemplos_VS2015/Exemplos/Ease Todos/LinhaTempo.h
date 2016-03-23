#ifndef LINHATEMPO_H
#define LINHATEMPO_H

#include "libUnicornio.h"
#include "uniEase.h"

class LinhaTempo
{
public:
	LinhaTempo();
	~LinhaTempo();

	void reset();
	void atualizar(float dt);
	void desenhar();

	Vetor2D pos;
	int alt;

	int inicio, fim;

	float tempo;
	float duracao;
	bool indo;
	bool parado;
};

#endif