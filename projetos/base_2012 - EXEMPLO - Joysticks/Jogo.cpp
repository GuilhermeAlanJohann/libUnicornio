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

	//	1)	carrega todos SpriteSheets (um para cada player)
	sheets[0].carregar("dados/imagens/player1.png", 1, 1);
	sheets[1].carregar("dados/imagens/player2.png", 1, 1);
	sheets[2].carregar("dados/imagens/player3.png", 1, 1);
	sheets[3].carregar("dados/imagens/player4.png", 1, 1);

	//	2)	"inicializa" players (seta SpriteSheets e posicao)
	for(int i = 0; i < MAXIMO_DE_PLAYERS; ++i)
	{
		players[i].setPos(res_x/5 * (i+1), res_y/2);
		players[i].setSpriteSheet(&sheets[i]);
	}

	//	3)	seta Joysticks para os players (passando o endereço dos joysticks da egl)
	players[0].setJoystick(&joysticks.player1);
	players[1].setJoystick(&joysticks.player2);
	players[2].setJoystick(&joysticks.player3);
	players[3].setJoystick(&joysticks.player4);
}

void Jogo::finalizar()
{
	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	4)	Atualiza a lógica de todos os players (move os personagens)
		for(int i = 0; i < MAXIMO_DE_PLAYERS; ++i)
		{
			players[i].atualizar();
		}

		//	5)	Desenha todos os players
		for(int i = 0; i < MAXIMO_DE_PLAYERS; ++i)
		{
			players[i].desenhar();
		}

		uniTerminarFrame();
	}
}