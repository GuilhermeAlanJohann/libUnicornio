#pragma once
#include "libUnicornio.h"
#include "GraficoEasing.h"
#include "Objeto.h"
#include "LinhaTempo.h"

#define MAX_FUNCS_EASING 11 

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();

	GraficoEasing botoes[MAX_FUNCS_EASING];
	int atual;

	Quad retan;

	GraficoEasing tipos[3];

	Objeto objetos[3];
	float duracaoMov;

	LinhaTempo linha;

	void setEaseFuncsTipos();
};

