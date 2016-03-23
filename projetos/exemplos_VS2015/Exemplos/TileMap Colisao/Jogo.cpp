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

	//	2)	Carregar recursos
	//			spritesheet para o player
	//			fonte para o texto de colisão
	gRecursos.carregarSpriteSheet("player", "assets/tilemap/spritesheets/player.png", 4, 4);
	gRecursos.carregarFonte("fonte colisao", "assets/tilemap/F25_Bank_Printer.ttf", 16, FONTE_ESTILO_NEGRITO);

	//	3)	Inicializar o personagem do player,
	//			passando o nome do spritesheet e o objeto que representa ele no mapa
	player.inicializar("player", mapa.getCamadaDeObjetos("Objetos")->getObjeto("Player"));

	//	4)	inicializar texto
	texto.setFonte("fonte colisao");
}

void Jogo::finalizar()
{
	//	11)	Descarregar recursos
	gRecursos.descarregarTudo();

	//	12)	Descarregar o tilemap
	mapa.descarregar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	5)	Verifica as teclas do teclado e caso forem pressionadas
		//		seta o destino do player
		atualizarInput();

		//	6)	Atualizar player
		player.atualizar();

		//	7)	TESTAR E TRATAR COLISÃO COM OS OBJETOS NO TILEMAP
		testarColisoes();

		//	8)	Centraliza o mapa na posicao do player
		mapa.setPosCentro(player.getX(), player.getY());

		//	9)	Desenhar o tilemap (player eh desenhado junto)
		mapa.desenhar();

		//	10) Desenhar texto da colisao
		texto.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 5);

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

void Jogo::testarColisoes()
{
	bool col_grama = testarColisaoComGramaAlta();
	bool col_arvore = testarColisaoComArvoreSeca();
	bool col_flor = testarColisaoComFlorRara();

	//	se nao esta colidindo com nada, 
	if (!col_grama && !col_arvore && !col_flor)
	{
		//	limpa o texto
		texto.apagar();
	}
}

bool Jogo::testarColisaoComGramaAlta()
{
	//	se existe um objeto do tipo "Grama Alta" na posicao do player
	if (mapa.existeObjetoDoTipoNaPos("Grama Alta", player.getX(), player.getY()))
	{
		//	setar texto
		texto.setString("Andando sobre grama alta!");

		//	esta colidindo
		return true;
	}

	//	nao esta colidindo
	return false;
}

bool Jogo::testarColisaoComArvoreSeca()
{
	//	se existe um objeto do tipo "Arvore Seca" na posicao do player
	if (mapa.existeObjetoDoTipoNaPos("Arvore Seca", player.getX(), player.getY()))
	{
		//	pega a propriedade chamada texto, contida do objeto do tipo "Arvore Seca"
		string txt = mapa.getObjetoDoTipoNaPos("Arvore Seca", player.getX(), player.getY())->getPropriedade("texto");

		//	setar string e alinhamento
		texto.setAlinhamento(TEXTO_CENTRALIZADO);
		texto.setString(txt);

		//	esta colidindo
		return true;
	}

	//	nao esta colidindo
	return false;
}

bool Jogo::testarColisaoComFlorRara()
{
	//	se existe um objeto do tipo "Flor Rara" na posicao do player
	if (mapa.existeObjetoDoTipoNaPos("Flor Rara", player.getX(), player.getY()))
	{
		//	pega o nome da flor
		string nome_flor = mapa.getObjetoDoTipoNaPos("Flor Rara", player.getX(), player.getY())->getNome();

		//	pega a propriedade chamada texto, contida do objeto do tipo "Flor Rara"
		string txt_flor = mapa.getObjetoDoTipoNaPos("Flor Rara", player.getX(), player.getY())->getPropriedade("texto");

		//	junta as strings, colocando um ' - ' entre elas
		string txt = nome_flor;
		txt.append("\n");
		txt.append(txt_flor);

		//	setar string e alinhamento
		texto.setAlinhamento(TEXTO_CENTRALIZADO);
		texto.setString(txt);

		//	esta colidindo
		return true;
	}

	//	nao esta colidindo
	return false;
}