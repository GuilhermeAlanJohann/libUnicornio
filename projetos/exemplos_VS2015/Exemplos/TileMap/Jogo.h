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
	void atualizarInput();
	void desenharInstrucoes();

	TileMap mapa;
	Personagem player;
};

