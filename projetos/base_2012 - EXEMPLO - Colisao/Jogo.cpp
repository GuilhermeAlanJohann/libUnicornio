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

	carregarSpriteSheets();

	inicializarNave();
	inicializarTiro();
}

void Jogo::finalizar()
{
	descarregarSpriteSheets();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		atualizarTudo();
		testarColisoes();
		desenharTudo();

		uniTerminarFrame();
	}
}

void Jogo::carregarSpriteSheets()
{
	recursos.carregarSpriteSheet("nave", "dados/imagens/nave.png", 1, 1);
	recursos.carregarSpriteSheet("tiro", "dados/imagens/tiro.png", 1, 2);
}

void Jogo::descarregarSpriteSheets()
{
	recursos.descarregarTodosSpriteSheets();
}

void Jogo::inicializarNave()
{
	int x, y;
	x = res_x/2;
	y = res_y - 30;

	nave.setSpriteSheet("nave");
	nave.setPos(x, y);
}

void Jogo::inicializarTiro()
{
	int x, y;
	x = res_x/2;
	y = -20;

	tiro.setSpriteSheet("tiro");
	tiro.setPos(x, y);
}

void Jogo::atualizarTudo()
{
	tiro.atualizar();
}

void Jogo::testarColisoes()
{
	//	colisao de tiro com nave
	if(uniColisao(tiro.getSprite(), tiro.getPosX(), tiro.getPosY(), tiro.getRot(),
				  nave.getSprite(), nave.getPosX(), nave.getPosY(), nave.getRot()))
	{
		tiro.setPos(tiro.getPosX(), -20);
	}

	//	colisao de mouse com tiro
	if(uniColisao(mouse.x, mouse.y, tiro.getSprite(), tiro.getPosX(), tiro.getPosY(), tiro.getRot()))
	{
		tiro.setPos(tiro.getPosX(), -20);
	}
}

void Jogo::desenharTudo()
{
	nave.desenhar();
	tiro.desenhar();
}