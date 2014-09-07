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

	mapa.carregar("dados/tilemaps/deserto_crateras.json");
	//mapa.carregarConfigTileSet("crater1", "dados/tilemaps/tilesets/crater1_config.txt");

	astar.inicializar(&mapa);
	astar.setHeuristica(HEURISTICA_EUCLIDEANA);
	astar.setMoverNaDiagonal(true);
	
	ss = new SpriteSheet();
	ss->carregar("dados/spritesheets/personagem.png", 4, 3);

	spr = new Sprite();
	spr->setSpriteSheet(ss);
	spr->setAncora(0.5, 0.75);

	mapa.getObjeto("Player")->setSprite(spr);

	vel = 0.8f;
}

void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!
	//	...

	astar.finalizar();

	delete spr;
	delete ss;

	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		if(mouse.pressionou[BOTAO_ESQ])
		{
			caminho.clear();
			indiceNodoAtual = 0;
			interpolador = 0.0f;
			float ox, oy;
			float dx, dy;
			mapa.getObjeto("Player")->obterPosCentro(ox, oy);
			mapa.pixelParaTile(mouse.x, mouse.y, dx, dy);

			bool achou = astar.calcularCaminho(ox, oy, dx, dy);
			if(achou)
				caminho = astar.getCaminho();
		}

		if(teclado.segurando[TECLA_ESQ])
			mapa.setX(mapa.getX() - 0.2);

		if(teclado.segurando[TECLA_DIR])
			mapa.setX(mapa.getX() + 0.2);

		if(teclado.segurando[TECLA_CIMA])
			mapa.setY(mapa.getY() - 0.2);

		if(teclado.segurando[TECLA_BAIXO])
			mapa.setY(mapa.getY() + 0.2);

		moverObjeto();

		mapa.desenhar();
		astar.desenharListaAberta();
		astar.desenharListaFechada();
		astar.desenharCaminho();

		uniDepurar("x", mapa.getX());
		uniDepurar("y", mapa.getY());
		uniDepurar("x_centro", mapa.getXCentro());
		uniDepurar("y_centro", mapa.getYCentro());

		uniTerminarFrame();
	}
}

void Jogo::moverObjeto()
{
	uniDepurar("interpolador", interpolador);
	uniDepurar("indiceNodo", indiceNodoAtual);

	if(caminho.empty())
		return;

	if(indiceNodoAtual >= caminho.size()-1)
		return;

	ObjetoTile* objeto = mapa.getObjeto("Player");

	objeto->getSprite()->avancarAnimacao();

	float x, y;
	objeto->obterPosCentro(x, y);

	x = caminho[indiceNodoAtual]->pos.x + caminho[indiceNodoAtual+1]->posRelativa.x*interpolador + 0.5;
	y = caminho[indiceNodoAtual]->pos.y + caminho[indiceNodoAtual+1]->posRelativa.y*interpolador + 0.5;

	objeto->setPosCentro(x, y);

	interpolador += deltaTempo*vel;
	while(interpolador >= 1.0f)
	{
		interpolador -= 1.0f;
		indiceNodoAtual++;
	}
}