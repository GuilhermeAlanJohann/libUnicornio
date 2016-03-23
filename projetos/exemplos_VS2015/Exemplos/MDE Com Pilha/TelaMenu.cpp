#include "TelaMenu.h"
#include "TelaJogo.h"


TelaMenu::TelaMenu()
{
}

TelaMenu::~TelaMenu()
{
}

void TelaMenu::aoEntrar()
{
	//	Inicializar a tela
	//		Carregar recursos
	gRecursos.carregarSpriteSheet("botaoPlay", "assets/maquina de estados/botao_play.png", 2, 1);
	gRecursos.carregarSpriteSheet("botaoExit", "assets/maquina de estados/botao_exit.png", 2, 1);

	//		Inicializar botões
	botaoPlay.setSpriteSheet("botaoPlay");
	botaoExit.setSpriteSheet("botaoExit");

	botaoPlay.setPos(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	botaoExit.setPos(gJanela.getLargura() / 2, 150 + gJanela.getAltura() / 2);

	clicouPlay = false;
	clicouExit = false;
}

void TelaMenu::aoSair()
{
	//	Finalizar a tela
	//		Descarregar recursos
	gRecursos.descarregarSpriteSheet("botaoPlay");
	gRecursos.descarregarSpriteSheet("botaoExit");
}

void TelaMenu::aoAtualizar(float dt)
{
	//	Se terminou o fade out, troca para a tela de jogo ou volta para a tela anterior
	//		Repare que aqui é usado o método "empilharEstado" e não o método "trocarEstado", 
	//		pois quando retornarmos da tela de jogo, queremos ver a tela de menu novamente.
	//		O método "desempilharEstado" simplesmente volta para a tela anterior, se não houver
	//		uma tela anterior, a maquina fica vazia.
	if (gJanela.fading.terminouFadeOut())
	{
		if(clicouPlay)
			getMaquinaDeEstadosComPilha()->empilharEstado(new TelaJogo);
		if (clicouExit)
			getMaquinaDeEstadosComPilha()->desempilharEstado();
		return;
	}

	//	Se ainda está executando o fade in ou fade out, retorna e não executa as linhas seguintes
	if (gJanela.fading.estaExecutando())
		return;


	//	Atualizar os botões
	botaoPlay.atualizar(dt);
	botaoExit.atualizar(dt);

	//	Se clicou no botão play,
	//		inicia o fade out e marca a variavel booleana para true.
	//		Precisamos dessa variavel para quando o fade out acabar,
	//		saber qual foi o botão clicado
	if (botaoPlay.estaClicado())
	{
		clicouPlay = true;
		gJanela.fading.iniciarFadeOut();
	}
	//	Se não, faz o mesmo para o botão exit
	else if (botaoExit.estaClicado())
	{
		clicouExit = true;
		gJanela.fading.iniciarFadeOut();
	}
}

void TelaMenu::aoDesenhar()
{
	//	Desenhar botões
	botaoPlay.desenhar();
	botaoExit.desenhar();
}