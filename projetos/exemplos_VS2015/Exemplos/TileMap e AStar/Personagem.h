#pragma once
#include "libUnicornio.h"
#include "TravessiaAStar.h"

enum AnimacaoPersonagem
{
	ANIMACAO_BAIXO,
	ANIMACAO_ESQ,
	ANIMACAO_DIR,
	ANIMACAO_CIMA
};

class Personagem
{
public:
	Personagem();
	~Personagem();

	void inicializar(string sheet, ObjetoTileMap* objeto, AStar* astar);

	void processarCliqueMouse(float mx, float my);
	void atualizar();

	Vetor2D getPos();

private:
	void atualizarTravessia();
	void atualizarAnimacao();

	TravessiaAStar travessia;
	ObjetoTileMap* objeto;
	AStar* astar;
	Sprite spr;

	float dest_x; 
	float dest_y;
	bool calcular_caminho;
};

