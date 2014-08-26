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
	//	métodos para inicialização
	void carregarSpriteSheets();
	void inicializarNave();
	void inicializarTiro();

	//	métodos para atualização/execução
	void atualizarTudo();
	void testarColisoes();
	void desenharTudo();


	//	atributos
	SpriteSheet ssTiro;
	SpriteSheet ssNave;

	Tiro tiro;
	Nave nave;
};

