#include "Tela.h"



Tela::Tela()
{
}

Tela::~Tela()
{
}

void Tela::entrar()
{
	//	Faz a inicializa��o do estado
	gJanela.fading.setDuracao(1.5f);	//	seta a dura��o do fade in e fade out
	gJanela.fading.cancelar();			//	garante que o fade out terminou
	gJanela.fading.iniciarFadeIn();		//	inicia o fade in
	gJanela.setCorDeFundo(30, 30, 30);	//	muda a cor de fundo

										//	chama o m�todo virtual que vai ser implementado na classe filha
	aoEntrar();
}

void Tela::sair()
{
	//	Faz a finaliza��o do estado
	//	(nada)

	//	chama o m�todo virtual que vai ser implementado na classe filha
	aoSair();
}

void Tela::atualizar(float dt)
{
	//	Separa o atualizar em duas partes:
	//		atualizar (l�gica)
	//		desenhar (graficos)

	aoAtualizar(dt);	//	m�todo virtual implementado pela classe filha
	aoDesenhar();		//	m�todo virtual implementado pela classe filha
}