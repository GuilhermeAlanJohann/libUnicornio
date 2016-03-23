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

	//	metodos para colisao
	void testarColisoes();
	bool testarColisaoComGramaAlta();
	bool testarColisaoComArvoreSeca();
	bool testarColisaoComFlorRara();

	//	atributos
	TileMap mapa;
	Personagem player;
	Texto texto;
};

