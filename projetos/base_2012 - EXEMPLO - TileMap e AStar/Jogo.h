#pragma once
#include "libUnicornio.h"
#include "Personagem.h"

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();

private:
	TileMap mapa;
	AStar astar;

	Personagem player;

	vector<NodoAStar> caminho;
	int nodoAtual;
	bool calcular_novo_caminho;
};

