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
	//	metodos para colisao
	void testarColisoes();
	bool colisaoGramaAlta();
	bool colisaoArvoreSeca();
	bool colisaoFlorRara();

	TileMap mapa;
	Personagem player;

	Texto texto;
};

