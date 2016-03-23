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
	void inicializarNave();
	void inicializarTiro();

	//	m�todo para testar colisoes e respoder a elas
	void testarColisoes();

	//	m�todo para desenhar intru��es na tela
	void desenharInstru��es();

	//	atributos
	Tiro tiro;
	Nave nave;
};

