#pragma once

#include "Tela.h"

//	Class para a tela de jogo
//		Essa classe simplesmente mostra um texto na tela.
//		Quando a tecla ENTER é pressionada, ela inicia o fade out.
//		Quando o fade out termina, ela rotorna para a tela anterior (TelaMenu)
class TelaJogo :public Tela
{
public:
	TelaJogo();
	~TelaJogo();

	void aoEntrar();
	void aoSair();
	void aoAtualizar(float dt);
	void aoDesenhar();

private:
	Texto txt;
};

