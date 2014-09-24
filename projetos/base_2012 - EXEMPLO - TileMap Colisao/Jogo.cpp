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

	//	3)	carregar fonte para o texto
	recursos.carregarFonte("fonte colisao", "dados/fontes/F25_Bank_Printer.ttf", 16);

	//	4)	inicializar o personagem do player,
			//	passando o nome do spritesheet e o objeto que representa ele no mapa
	player.inicializar("player", mapa.getObjeto("Player"));

	//	5)	inicializar texto
	texto.setFonte("fonte colisao");
}

void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!
	//	...

	//	12)	descarregar spritesheets e fontes
	recursos.descarregarTudo();

	//	13)	descarregar o tilemap
	mapa.descarregar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	6)	atualizar player
		player.atualizar();

		//	7)	mover player
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

		//	8)	TESTAR E TRATAR COLISAO COM OBJETOS NO TILEMAP
		testarColisoes();

		//	9)	centraliza o mapa na posicao do player
		mapa.setPosCentro(player.getX(), player.getY());

		//	10)	desenhar o tilemap (player eh desenhado junto)
		mapa.desenhar();

		//	11) desenhar texto da colisao
		texto.desenhar(res_x/2, res_y/5);

		uniTerminarFrame();
	}
}

void Jogo::testarColisoes()
{
	bool col_grama = colisaoGramaAlta();
	bool col_arvore = colisaoArvoreSeca();
	bool col_flor = colisaoFlorRara();

	//	se nao esta colidindo com nada, 
	if(!col_grama && !col_arvore && !col_flor)
	{
		//	limpa o texto
		texto.apagar();
	}
}

bool Jogo::colisaoGramaAlta()
{
	//	se existe um objeto do tipo "Grama Alta" na posicao do player
	if(mapa.existeObjetoDoTipoNaPos("Grama Alta", player.getX(), player.getY()))
	{
		//	setar texto
		texto.setTexto("Andando sobre grama alta!");

		//	esta colidindo
		return true;
	}

	//	nao esta colidindo
	return false;
}

bool Jogo::colisaoArvoreSeca()
{
	//	se existe um objeto do tipo "Arvore Seca" na posicao do player
	if(mapa.existeObjetoDoTipoNaPos("Arvore Seca", player.getX(), player.getY()))
	{
		//	pega a propriedade chamada texto, contida do objeto do tipo "Arvore Seca"
		string txt = mapa.getObjetoDoTipoNaPos("Arvore Seca", player.getX(), player.getY())->getPropriedade("texto");

		//	setar texto
		texto.setTexto(txt);

		//	esta colidindo
		return true;
	}

	//	nao esta colidindo
	return false;
}

bool Jogo::colisaoFlorRara()
{
	//	se existe um objeto do tipo "Flor Rara" na posicao do player
	if(mapa.existeObjetoDoTipoNaPos("Flor Rara", player.getX(), player.getY()))
	{
		//	pega o nome da flor
		string nome_flor = mapa.getObjetoDoTipoNaPos("Flor Rara", player.getX(), player.getY())->getNome();

		//	pega a propriedade chamada texto, contida do objeto do tipo "Flor Rara"
		string txt_flor = mapa.getObjetoDoTipoNaPos("Flor Rara", player.getX(), player.getY())->getPropriedade("texto");

		//	junta as strings, colocando um ' - ' entre elas
		string txt = nome_flor;
		txt.append(" - ");
		txt.append(txt_flor);

		//	setar texto
		texto.setTexto(txt);

		//	esta colidindo
		return true;
	}

	//	nao esta colidindo
	return false;
}