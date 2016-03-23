#include "Menu.h"


Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::inicializar()
{
	//	1) Carregar os spritesheets para os botões
	gRecursos.carregarSpriteSheet("botao_vermelho", "assets/botaosprite/vermelho.png", 3, 1);
	gRecursos.carregarSpriteSheet("botao_verde", "assets/botaosprite/verde.png", 3, 1);
	gRecursos.carregarSpriteSheet("botao_azul", "assets/botaosprite/azul.png", 3, 1);

	//	2) Setar spritesheet nos botões
	botaoVermelho.setSpriteSheet("botao_vermelho");
	botaoVerde.setSpriteSheet("botao_verde");
	botaoAzul.setSpriteSheet("botao_azul");

	//	3) Posiciona os botões
	botaoVermelho.setPos(gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 100);
	botaoVerde.setPos(   gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	botaoAzul.setPos(    gJanela.getLargura() / 2, gJanela.getAltura() / 2 + 100);

}

void Menu::finalizar()
{
	//	Descarregar spritesheets
	gRecursos.descarregarSpriteSheet("botao_vermelho");
	gRecursos.descarregarSpriteSheet("botao_verde");
	gRecursos.descarregarSpriteSheet("botao_azul");
}

void Menu::atualizar()
{
	//	4) Atualizar todos os botões
	botaoVermelho.atualizar();
	botaoVerde.atualizar();
	botaoAzul.atualizar();

	//	5) Verificar clique nos botões e reponder
	if(botaoVermelho.estaClicado())
		gJanela.setCorDeFundo(255, 0, 0);	//	muda cor de fundo para vermelho

	if(botaoVerde.estaClicado())
		gJanela.setCorDeFundo(0, 255, 0);	//	muda cor de fundo para verde

	if(botaoAzul.estaClicado())
		gJanela.setCorDeFundo(0, 0, 255);	//	muda cor de fundo para azul
}

void Menu::desenhar()
{
	//	6) Desenha os botões
	botaoVermelho.desenhar();
	botaoVerde.desenhar();
	botaoAzul.desenhar();
}