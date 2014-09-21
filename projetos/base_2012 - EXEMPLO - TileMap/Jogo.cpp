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

	//	1)	carregar o tilemap
	mapa.carregar("dados/tilemaps/mapa_campo.json");

	//	2)	carregar spritesheet para o player
	recursos.carregarSpriteSheet("player", "dados/spritesheets/player.png", 4, 4);

	//	3)	inicializar o personagem do player,
			//	passando o nome do spritesheet e o objeto que representa ele no mapa
	player.inicializar("player", mapa.getObjeto("Player"));
}

void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!
	//	...

	//	8)	descarregar spritesheet
	recursos.descarregarTudo();

	//	9)	descarregar o tilemap
	mapa.descarregar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	4)	atualizar player
		player.atualizar();

		//	5)	mover player
		if(!player.estaMovendo())
		{
			if(teclado.segurando[TECLA_DIR])
			{
				if(mapa.tileECaminhavel(player.getX() + 1.0, player.getY()))
				{
					player.moverPara(player.getX() + 1.0, player.getY());
				}
			}
			else if(teclado.segurando[TECLA_ESQ])
			{
				if(mapa.tileECaminhavel(player.getX() - 1.0, player.getY()))
				{
					player.moverPara(player.getX() - 1.0, player.getY());
				}
			}
			else if(teclado.segurando[TECLA_CIMA])
			{
				if(mapa.tileECaminhavel(player.getX(), player.getY() - 1.0))
				{
					player.moverPara(player.getX(), player.getY() - 1.0);
				}
			}
			else if(teclado.segurando[TECLA_BAIXO])
			{
				if(mapa.tileECaminhavel(player.getX(), player.getY() + 1.0))
				{
					player.moverPara(player.getX(), player.getY() + 1.0);
				}
			}
		}

		//	6)	centraliza o mapa na posicao do player
		mapa.setPosCentro(player.getX(), player.getY());

		//	7)	desenhar o tilemap (player eh desenhado junto)
		mapa.desenhar();

		uniTerminarFrame();
	}
}