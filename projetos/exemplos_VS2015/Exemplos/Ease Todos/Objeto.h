#ifndef OBJETO_H
#define OBJETO_H

#include "GraficoEasing.h"
#include "Vetor2D.h"

class Objeto
{
public:
	Objeto();
	~Objeto();

	void reset();
	void atualizar(float dt);
	void desenhar();

	Vetor2D pos;
	Vetor2D tam;

	Vetor2D posInicial;
	Vetor2D posFinal;

	float duracao;

	Cor cor;

	GraficoEasing* grafico;

	float tempo;
	bool indo;
	bool parado;
};

#endif