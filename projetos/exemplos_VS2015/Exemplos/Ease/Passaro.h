#pragma once

#include "libUnicornio.h"

class Passaro
{
public:
	Passaro();
	~Passaro();

	void inicializar();

	void atualizar();
	void desenhar();

private:
	Sprite spr;
	Vetor2D pos;
	Vetor2D posInicio;
	Vetor2D destino;
	float tempo;
	float duracaoMov;
};

