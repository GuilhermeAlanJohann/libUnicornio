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
	ssVermelho.carregar("dados/spritesheets/botao_vermelho.png", 1, 3);
	ssVerde.carregar("dados/spritesheets/botao_verde.png", 1, 3);
	ssAzul.carregar("dados/spritesheets/botao_azul.png", 1, 3);

	//	inicializa os botoes
	botaoVermelho.inicializar(&ssVermelho);
	botaoVerde.inicializar(&ssVerde);
	botaoAzul.inicializar(&ssAzul);

	//	posiciona os botoes
	botaoVermelho.setPos(res_x/2, res_y/2 - 100);
	botaoVerde.setPos(res_x/2, res_y/2);
	botaoAzul.setPos(res_x/2, res_y/2 + 100);

}

void Menu::finalizar()
{
	//	finaliza os botoes
	botaoVermelho.finalizar();
	botaoVerde.finalizar();
	botaoAzul.finalizar();
}

void Menu::atualizar()
{
	//	atualiza todos os botoes
	botaoVermelho.atualizar();
	botaoVerde.atualizar();
	botaoAzul.atualizar();

	//	processa os cliques nos botoes
	if(botaoVermelho.clicou())
		uniSetCorDeFundo(255, 0, 0);	//	muda cor de fundo para vermelho
	if(botaoVerde.clicou())
		uniSetCorDeFundo(0, 255, 0);	//	muda cor de fundo para verde
	if(botaoAzul.clicou())
		uniSetCorDeFundo(0, 0, 255);	//	muda cor de fundo para azul
}

void Menu::desenhar()
{
	//	desenha os botoes
	botaoVermelho.desenhar();
	botaoVerde.desenhar();
	botaoAzul.desenhar();
}