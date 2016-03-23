#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(800, 600, false);

	//	Inicializa o menu
	menu.inicializar();
}

void Jogo::finalizar()
{
	//	Finaliza o menu
	menu.finalizar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	Atualiza a logica do menu
		menu.atualizar();

		//	Desenha o menu
		menu.desenhar();

		uniTerminarFrame();
	}
}