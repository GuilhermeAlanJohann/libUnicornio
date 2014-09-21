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
	recursos.carregarSpriteSheet("player1", "dados/imagens/player1.png", 1, 1);
	recursos.carregarSpriteSheet("player2", "dados/imagens/player2.png", 1, 1);
	recursos.carregarSpriteSheet("player3", "dados/imagens/player3.png", 1, 1);
	recursos.carregarSpriteSheet("player4", "dados/imagens/player4.png", 1, 1);

	//	2)	"inicializa" players (seta SpriteSheets e posicao)
	for(int i = 0; i < MAXIMO_DE_PLAYERS; ++i)
	{
		//	posicao
		players[i].setPos(res_x/5 * (i+1), res_y/2);
	}
	//	spritesheets
	players[0].setSpriteSheet("player1");
	players[1].setSpriteSheet("player2");
	players[2].setSpriteSheet("player3");
	players[3].setSpriteSheet("player4");

	//	3)	seta Joysticks para os players (passando o endereço dos joysticks da egl)
	players[0].setJoystick(&joysticks.player1);
	players[1].setJoystick(&joysticks.player2);
	players[2].setJoystick(&joysticks.player3);
	players[3].setJoystick(&joysticks.player4);
}

void Jogo::finalizar()
{
	//	6)	descarregar tudo
	recursos.descarregarTudo();

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