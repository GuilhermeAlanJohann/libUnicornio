#pragma once
#include "Tela.h"

//	Class para a tela de jogo
//		Essa classe simplesmente mostra dois bot�es na tela:
//			Play e Exit
//		Quando um dos bot�es � pressionado, ela inicia o fade out.
//		Quando o fade out termina, ela responde ao clique dos bot�es 
//			se clicou em Play, avan�a para a pr�xima tela (TelaJogo),
//			se clicou em Exit, rotorna para a tela anterior (Nenhuma Tela).
class TelaMenu :public Tela
{
public:
	TelaMenu();
	~TelaMenu();

	void aoEntrar();
	void aoSair();
	void aoAtualizar(float dt);
	void aoDesenhar();

private:
	BotaoSprite botaoPlay;
	BotaoSprite botaoExit;
	bool clicouPlay;
	bool clicouExit;
};

