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

	//	1)	Carregar todos SpriteSheets (um para cada player)
	gRecursos.carregarSpriteSheet("player1", "assets/joysticks/player1.png", 2, 5);
	gRecursos.carregarSpriteSheet("player2", "assets/joysticks/player2.png", 2, 4);
	gRecursos.carregarSpriteSheet("player3", "assets/joysticks/player3.png", 2, 5);
	gRecursos.carregarSpriteSheet("player4", "assets/joysticks/player4.png", 2, 4);

	//	Ajustar o número de frames em cada animação
	gRecursos.getSpriteSheet("player1")->setNumFramesDaAnimacao(0, 2);	//	anim 0, 2 frames
	gRecursos.getSpriteSheet("player2")->setNumFramesDaAnimacao(0, 2);	//	anim 0, 2 frames
	gRecursos.getSpriteSheet("player3")->setNumFramesDaAnimacao(0, 2);	//	anim 0, 2 frames
	gRecursos.getSpriteSheet("player4")->setNumFramesDaAnimacao(0, 2);	//	anim 0, 2 frames

	//	2)	"Inicializar" players (seta SpriteSheets, posicao e joystick)
	for(int i = 0; i < MAXIMO_DE_PLAYERS; ++i)
	{
		players[i].setSpriteSheet("player" + to_string(i+1));
		players[i].setPos(gJanela.getLargura()/5 * (i+1), gJanela.getAltura()/2);
		players[i].setJoystick(i);
	}
}

void Jogo::finalizar()
{
	//	5)	Descarregar tudo
	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	3)	Atualizar a lógica de todos os players (move os personagens)
		for(int i = 0; i < MAXIMO_DE_PLAYERS; ++i)
		{
			players[i].atualizar();
		}

		//	4)	Desenhar todos os players
		for(int i = 0; i < MAXIMO_DE_PLAYERS; ++i)
		{
			players[i].desenhar();
		}

		desenharInstrucoes();

		uniTerminarFrame();
	}
}

void Jogo::desenharInstrucoes()
{
	string txt = "Instruções:\n"
		"    Conecte até 4 joysticks.\n"
		"    Mova o analógico esquerdo dos joysticks para mover os personagens.";

	gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
}