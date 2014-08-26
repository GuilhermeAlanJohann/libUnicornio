#pragma once
#include "libUnicornio.h"
#include "AStar.h"

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();

private:
	void moverObjeto();

	TileMap mapa;
	AStar astar;

	Sprite* spr;
	SpriteSheet* ss;

	float vel;
	vector<NodoAStar*> caminho;
	int indiceNodoAtual;
	float interpolador;
};

