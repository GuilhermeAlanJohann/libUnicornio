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
	mapa.carregar("assets/tilemap/tilemaps/mapa_campo.json");

	//	2)	inicializar A* com o mapa carregado
	astar.inicializar(&mapa);

	//	3)	configurar A*
	astar.setHeuristica(HEURISTICA_EUCLIDIANA);
	astar.setEvitarDiagonaisFechadas(true);
	astar.setMoverNaDiagonal(false);

	//	4)	carregar spritesheet para o player
	gRecursos.carregarSpriteSheet("player", "assets/tilemap/spritesheets/player.png", 4, 4);

	//	5)	inicializar o personagem do player,
			//	passando o nome do spritesheet, o objeto que representa ele no mapa e um ponteiro para o A*.
			//	Estamos passando um ponteiro para o A*, ao invez de criar um objeto dentro da classe
			//	pois assim podemos reutiliza-lo para vários personagens, economizando MUITA memória.
	player.inicializar("player", mapa.getObjeto("Player"), &astar);
}

void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!
	//	...

	//	10)	descarregar spritesheet
	gRecursos.descarregarTudo();

	//	11)	descarregar o tilemap
	mapa.descarregar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	6)	Se o jogador clicar com o mouse,
		if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
		{
			//	transforma a posição do mouse de coordenadas de tela para coodenadas de tiles do mapa
			float mouse_x_em_tiles;
			float mouse_y_em_tiles;
			mapa.telaParaTile(gMouse.x, gMouse.y, mouse_x_em_tiles, mouse_y_em_tiles);

			//	passa posição do mouse em tiles para o personagem processar
			player.processarCliqueMouse(mouse_x_em_tiles, mouse_y_em_tiles);
		}

		//	7)	atualizar player
		player.atualizar();

		//	8)	centraliza o mapa na posicao do player
		mapa.setPosCentro(player.getPos().x, player.getPos().y);

		//	9)	desenhar o tilemap (player é desenhado junto)
		mapa.desenhar();

		//	[OPCIONAL] - desenhar informacoes do A*
		astar.desenharListaAberta(&mapa);
		astar.desenharListaFechada(&mapa);
		astar.desenharCaminho(&mapa);

		uniTerminarFrame();
	}
}