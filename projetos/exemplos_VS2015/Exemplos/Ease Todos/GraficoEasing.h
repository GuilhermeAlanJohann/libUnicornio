#ifndef GRAFICOEASING_H
#define GRAFICOEASING_H

#include "libUnicornio.h"
#include "uniEase.h"

#define EaseFunc (float)(*easefunc)(float, float, float, float)

class GraficoEasing
{
public:
	GraficoEasing();
	~GraficoEasing();

	bool clicou();
	void desenhar();

	Vetor2D pos;
	Vetor2D tam;
	Cor cor;
	string nome;
	float (*easefunc)(float tempo, float duracao, float inicio, float deslocamento);
};

#endif