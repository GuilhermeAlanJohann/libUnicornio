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
	void inicializarNave();
	void inicializarTiro();

	//	método para testar colisoes e respoder a elas
	void testarColisoes();

	//	método para desenhar intruções na tela
	void desenharInstruções();

	//	atributos
	Tiro tiro;
	Nave nave;
};

