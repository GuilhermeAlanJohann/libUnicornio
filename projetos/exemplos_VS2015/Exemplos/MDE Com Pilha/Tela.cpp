#include "Tela.h"



Tela::Tela()
{
}

Tela::~Tela()
{
}

void Tela::entrar()
{
	//	Faz a inicialização do estado
	gJanela.fading.setDuracao(1.5f);	//	seta a duração do fade in e fade out
	gJanela.fading.cancelar();			//	garante que o fade out terminou
	gJanela.fading.iniciarFadeIn();		//	inicia o fade in
	gJanela.setCorDeFundo(30, 30, 30);	//	muda a cor de fundo

										//	chama o método virtual que vai ser implementado na classe filha
	aoEntrar();
}

void Tela::sair()
{
	//	Faz a finalização do estado
	//	(nada)

	//	chama o método virtual que vai ser implementado na classe filha
	aoSair();
}

void Tela::atualizar(float dt)
{
	//	Separa o atualizar em duas partes:
	//		atualizar (lógica)
	//		desenhar (graficos)

	aoAtualizar(dt);	//	método virtual implementado pela classe filha
	aoDesenhar();		//	método virtual implementado pela classe filha
}