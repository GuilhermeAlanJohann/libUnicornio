#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	//	1) Iniciar a biblioteca em tela cheia (terceiro par�metro = true)
	uniInicializar(800, 600, true);

	//	Carrega spritesheet para o fundo
	gRecursos.carregarSpriteSheet("fundo", "assets/comum/fundo.png");
	//	Seta spritesheet
	sprFundo.setSpriteSheet("fundo");

	gDebug.setPos(50, 150);
}

void Jogo::finalizar()
{
	//	Descarregar tudo (spritesheet)
	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	2) Ajstar o tamanho da tela, conforme o usu�rio quiser
		if (gTeclado.pressionou[TECLA_1])
			gJanela.setTamanho(800, 600);
		else if (gTeclado.pressionou[TECLA_2])
			gJanela.setTamanho(640, 960);
		else if (gTeclado.pressionou[TECLA_3])
			gJanela.setTamanho(1080, 720);
		//	3) Remover o letterboxing
		else if (gTeclado.pressionou[TECLA_ENTER])
			gJanela.removerLetterBoxing();

		//	Depurar a posi��o d mouse
		gDebug.depurar("mouse", Vetor2D(gMouse.x, gMouse.y));

		//	Desenhar o fundo
		sprFundo.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

		//	Desenhar Instru��es
		desenharInstrucoes();

		uniTerminarFrame();
	}
}

void Jogo::desenharInstrucoes()
{
	string txt = "Instru��es:\n"
		"    Pressione [1], [2], ou [3] para trocar o tamanho da tela.\n"
		"    Pressione [ENTER] para remover o letterboxing.\n"
		"    Repare que a posi��o do mouse ir� mudar quando remover o letterboxing!\n"
		"    Isso acontece pois as dimen��es da tela mudaram.\n"
		"    O jogo deve estar ciente de que isso acontece se ser programado levando isso em conta.";

	gGraficos.desenharTexto(txt, 25, 25, 0, 0, 0, 255, 0, 0);
}