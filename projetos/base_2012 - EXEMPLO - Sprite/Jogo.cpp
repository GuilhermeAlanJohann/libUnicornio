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

	//	1) inicializa player
	player.inicializar();
}

void Jogo::finalizar()
{
	//	4) finaliza player
	player.finalizar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	2)	atualiza lógica do player (move personagem(s))
		player.atualizar();

		//	3)	desenha player (desenha personagem(s) do player)
		player.desenhar();

		uniTerminarFrame();
	}
}