#pragma once

#include "libUnicornio.h"
#include "Personagem.h"

class Mapa
{
public:
	Mapa();
	~Mapa();

	void inicializar(int tilesX, int tilesY, int largTile, int altTile);
	void finalizar();

	void atualizar();
	void desenhar();

	void telaParaTile(int x, int y, float& tx, float& ty);
	void tileParaTela(float tx, float ty, int& x, int& y);

	void centralizar(float tx, float ty);

	AStar* getAStar();

	int getTilesEmX();
	int getTilesEmY();

private:
	int esq;
	int cima;
	int tilesEmX;
	int tilesEmY;
	int largTile;
	int altTile;
	AStar astar;

	Personagem personagem;
};

