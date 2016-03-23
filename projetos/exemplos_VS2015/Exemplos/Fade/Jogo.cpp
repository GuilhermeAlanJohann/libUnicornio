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

	//	carregar e setar spritesheet para o fundo.
	gRecursos.carregarSpriteSheet("fundo", "assets/comum/fundo.png");
	sprFundo.setSpriteSheet("fundo");

	gJanela.setCorDeFundo(255, 255, 255);

	//	(Opcional) Muda a cor do fade
	//		O padrão já é preto.
	gJanela.fading.setCor(0, 0, 0, 255);

	//	(Opcional) Muda a duração do fade
	gJanela.fading.setDuracao(2.0f);	// 2 segundos

	//	1) Iniciar fade in
	gJanela.fading.iniciarFadeIn();
}

void Jogo::finalizar()
{
	//	Descarregar todos os recursos
	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	2) Muda o fade somente quando não está executando.
		if (!gJanela.fading.estaExecutando())
		{
			if (gTeclado.pressionou[TECLA_I])
			{
				gJanela.fading.iniciarFadeIn();		//	iniciar fade in
			}
			if (gTeclado.pressionou[TECLA_O])
			{
				gJanela.fading.iniciarFadeOut();	//	iniciar fade out
			}
		}

		//	3) Se terminou o fade in
		if (gJanela.fading.terminouFadeIn())
		{
			//	4) É necessário manualmente setar a variavel para false.
			gJanela.fading.setTerminouFadeIn(false);

			//	(Opcional) Faz alguma coisa quando terminou o fade in
			//	Ex: iniciar a fase
			
		}
		//	5) Se terminou o fade out
		else if (gJanela.fading.terminouFadeOut())
		{
			//	6) É necessário manualmente setar a variavel para false.
			gJanela.fading.setTerminouFadeOut(false);

			//	(Opcional) Faz alguma coisa quando terminou o fade out
			//	Ex: trocar de tela
		}

		//	Desenhar fundo e instruções
		sprFundo.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
		desenharInstrucoes();

		uniTerminarFrame();
	}
}

void Jogo::desenharInstrucoes()
{
	string txt = "Instruções:\n"
		"    Pressione [I] pra executar o fade in.\n"
		"    Pressione [O] pra executar o fade out.";

	gGraficos.desenharTexto(txt, 25, 25, 0, 0, 0, 255, 0, 0);
}