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

	//	1)	Carregar o tilemap
	mapa.carregar("assets/tilemap/tilemaps/mapa_campo.json");

	//	2)	Carregar spritesheet para o player
	gRecursos.carregarSpriteSheet("player", "assets/tilemap/spritesheets/player.png", 4, 4);

	//	3)	Inicializar o personagem do player,
			//	passando o nome do spritesheet e o objeto que representa ele no mapa
	player.inicializar("player", mapa.getCamadaDeObjetos("Objetos")->getObjeto("Player"));
}

void Jogo::finalizar()
{
	//	8)	descarregar spritesheet
	gRecursos.descarregarTudo();

	//	9)	descarregar o tilemap
	mapa.descarregar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	4)	Verifica as teclas do teclado e caso forem pressionadas
		//		seta o destino do player
		atualizarInput();

		//	5)	Atualizar player
		player.atualizar();

		//	6)	centraliza o mapa na posicao do player
		mapa.setPosCentro(player.getX(), player.getY());

		//	7)	desenhar o tilemap (player eh desenhado junto)
		mapa.desenhar();


		//	Desenhar instruções
		desenharInstrucoes();

		uniTerminarFrame();
	}
}

void Jogo::atualizarInput()
{
	if (!player.estaMovendo())
	{
		if (gTeclado.segurando[TECLA_DIR])
		{
			if (mapa.tileECaminhavel(player.getX() + 1.0, player.getY()))
			{
				player.setDestino(player.getX() + 1.0, player.getY());
			}
		}
		else if (gTeclado.segurando[TECLA_ESQ])
		{
			if (mapa.tileECaminhavel(player.getX() - 1.0, player.getY()))
			{
				player.setDestino(player.getX() - 1.0, player.getY());
			}
		}
		else if (gTeclado.segurando[TECLA_CIMA])
		{
			if (mapa.tileECaminhavel(player.getX(), player.getY() - 1.0))
			{
				player.setDestino(player.getX(), player.getY() - 1.0);
			}
		}
		else if (gTeclado.segurando[TECLA_BAIXO])
		{
			if (mapa.tileECaminhavel(player.getX(), player.getY() + 1.0))
			{
				player.setDestino(player.getX(), player.getY() + 1.0);
			}
		}
	}
}

void Jogo::desenharInstrucoes()
{
	string txt = "Instruções:\n"
		"    Use as setas para mover o personagem.";

	gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
}