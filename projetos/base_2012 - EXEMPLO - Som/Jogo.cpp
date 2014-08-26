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

	//	1)	inicializa o tocador
	tocador.inicializar();
}

void Jogo::finalizar()
{
	//	4)	finaliza o tocador
	tocador.finalizar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	2)	atualiza a lógica do tocador
		tocador.atualizar();

		//	3)	desenha as intruções na tela
		tocador.desenharInstrucoes();

		uniTerminarFrame();
	}
}