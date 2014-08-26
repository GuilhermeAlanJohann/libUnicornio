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

	//	1) inicializa o menu
	menu.inicializar();
}

void Jogo::finalizar()
{
	//	4) finaliza o menu
	menu.finalizar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	2) atualiza a logica do menu
		menu.atualizar();

		//	3) desenha o menu
		menu.desenhar();

		uniTerminarFrame();
	}
}