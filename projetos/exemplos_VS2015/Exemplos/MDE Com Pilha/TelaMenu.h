#pragma once
#include "Tela.h"

//	Class para a tela de jogo
//		Essa classe simplesmente mostra dois botões na tela:
//			Play e Exit
//		Quando um dos botões é pressionado, ela inicia o fade out.
//		Quando o fade out termina, ela responde ao clique dos botões 
//			se clicou em Play, avança para a próxima tela (TelaJogo),
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

