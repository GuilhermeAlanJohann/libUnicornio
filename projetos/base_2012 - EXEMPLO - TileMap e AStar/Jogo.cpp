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

	//	2)	inicializar A* com o mapa carregado
	astar.inicializar(&mapa);

	//	3)	configurar A*
	astar.setHeuristica(HEURISTICA_EUCLIDEANA);
	astar.setEvitarDiagonaisFechadas(true);
	astar.setMoverNaDiagonal(false);
	nodoAtual = 0;
	calcular_novo_caminho = false;

	//	4)	carregar spritesheet para o player
	sheetPlayer.carregar("dados/spritesheets/player.png", 4, 4);

	//	5)	inicializar o personagem do player,
			//	passando o spritesheet e o objeto que representa ele no mapa
	player.inicializar(&sheetPlayer, mapa.getObjeto("Player"));
}

void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!
	//	...

	//	11)	limpar caminho
	caminho.clear();

	//	12)	descarregar spritesheet
	sheetPlayer.descarregar();

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

		//	7)	calcular caminho quando clicar com o mouse em um local do mapa
		if(mouse.pressionou[BOTAO_ESQ])
		{
			calcular_novo_caminho = true;
		}

		//	7.1)	espera ate que o player tenha parado de se mover para calcular um novo caminho
		if(calcular_novo_caminho && !player.estaMovendo())
		{
			float mouse_x_em_tiles;
			float mouse_y_em_tiles;

			mapa.pixelParaTile(mouse.x, mouse.y, mouse_x_em_tiles, mouse_y_em_tiles);

			bool achou = astar.calcularCaminho(player.getX(), player.getY(), mouse_x_em_tiles, mouse_y_em_tiles);
			caminho.clear();

			if(achou)
			{
				caminho = astar.getCaminho();
				nodoAtual = 1;	//	ignora a primeira posicao
			}

			calcular_novo_caminho = false;
		}

		//	8)	mover player
		if(!player.estaMovendo() && nodoAtual < caminho.size())
		{
			player.moverPara(caminho[nodoAtual].pos.x + 0.5, caminho[nodoAtual].pos.y + 0.5);
			nodoAtual++;
		}

		//	9)	centraliza o mapa na posicao do player
		mapa.setPosCentro(player.getX(), player.getY());

		//	10)	desenhar o tilemap (player eh desenhado junto)
		mapa.desenhar();

		//	[OPCIONAL] - desenhar informacoes do A*
		astar.desenharListaAberta();
		astar.desenharListaFechada();
		astar.desenharCaminho();

		uniTerminarFrame();
	}
}