#pragma once
#include "Nave.h"
#include "Tiro.h"
#include <vector>

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();

private:
	//	m�todos para inicializa��o
	void carregarSpriteSheets();
	void descarregarSpriteSheets();
	void inicializarNave();
	void inicializarTiro();

	//	m�todos para atualiza��o/execu��o
	void atualizarTudo();
	void testarColisoes();
	void desenharTudo();


	//	atributos
	Tiro tiro;
	Nave nave;
};

