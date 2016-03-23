#include "TelaInicial.h"
#include "TelaMenu.h"


TelaInicial::TelaInicial()
{
}

TelaInicial::~TelaInicial()
{
}

void TelaInicial::aoEntrar()
{
	//	Inicializa a tela
	gRecursos.carregarSpriteSheet("logo", "assets/maquina de estados/logo unicornio.png");
	spr.setSpriteSheet("logo");

	tempo = 0.0f;
	duracao = 3.0f;		//	3 segundos
}

void TelaInicial::aoSair()
{
	//	Finaliza a tela
	gRecursos.descarregar("logo");
}

void TelaInicial::aoAtualizar(float dt)
{
	//	?)	Se terminou o fade out, troca para a tela de menu
	//			Repare que aqui � usado o m�todo "trocarEstado" e n�o o m�todo "empilharEstado", 
	//			pois quando retornarmos do menu, n�o queremos ver a tela de inicio novamente.
	if (gJanela.fading.terminouFadeOut())
	{
		getMaquinaDeEstados()->trocarEstado(new TelaMenu);
		return;
	}

	//	?)	Se ainda est� executando o fade in ou fade out, retorna e n�o executa as linhas seguintes
	if (gJanela.fading.estaExecutando())
		return;

	//	?)	Controla o tempo para iniciar o fade out
	tempo += dt;	//	soma o tempo que passou no ultimo frame (delta tempo)
	if (tempo >= duracao)
	{
		gJanela.fading.iniciarFadeOut();
	}
}

void TelaInicial::aoDesenhar()
{
	spr.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
}