#pragma once

#include "libUnicornio.h"

class Mapa;

class Personagem
{
public:
	Personagem();
	~Personagem();

	void inicializar(Mapa* mapa);
	void atualizar();
	void desenhar();

private:
	Sprite spr;
	Vetor2D pos;
	Vetor2D destino;
	Mapa* mapa;
	TravessiaAStar travessia;
	bool calc_caminho;
};

