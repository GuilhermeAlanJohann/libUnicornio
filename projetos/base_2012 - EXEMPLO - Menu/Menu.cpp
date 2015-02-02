#include "Menu.h"


Menu::Menu()
{
}

Menu::~Menu()
{
}


void Menu::inicializar()
{
	//	carrega os spritesheets para os botoes
	recursos.carregarSpriteSheet("botao_vermelho", "dados/spritesheets/botao_vermelho.png", 3, 1);
	recursos.carregarSpriteSheet("botao_verde", "dados/spritesheets/botao_verde.png", 3, 1);
	recursos.carregarSpriteSheet("botao_azul", "dados/spritesheets/botao_azul.png", 3, 1);

	//	setar spritesheet nos botoes
	botaoVermelho.setSpriteSheet("botao_vermelho");
	botaoVerde.setSpriteSheet("botao_verde");
	botaoAzul.setSpriteSheet("botao_azul");

	//	posiciona os botoes
	botaoVermelho.setPos(res_x/2, res_y/2 - 100);
	botaoVerde.setPos(res_x/2, res_y/2);
	botaoAzul.setPos(res_x/2, res_y/2 + 100);

}

void Menu::finalizar()
{
	//	descarregar spritesheets
	recursos.descarregarSpriteSheet("botao_vermelho");
	recursos.descarregarSpriteSheet("botao_verde");
	recursos.descarregarSpriteSheet("botao_azul");
}

void Menu::atualizar()
{
	//	atualiza todos os botoes
	botaoVermelho.atualizar();
	botaoVerde.atualizar();
	botaoAzul.atualizar();

	//	processa os cliques nos botoes
	if(botaoVermelho.estaClicado())
		uniSetCorDeFundo(255, 0, 0);	//	muda cor de fundo para vermelho
	if(botaoVerde.estaClicado())
		uniSetCorDeFundo(0, 255, 0);	//	muda cor de fundo para verde
	if(botaoAzul.estaClicado())
		uniSetCorDeFundo(0, 0, 255);	//	muda cor de fundo para azul
}

void Menu::desenhar()
{
	//	desenha os botoes
	botaoVermelho.desenhar();
	botaoVerde.desenhar();
	botaoAzul.desenhar();
}