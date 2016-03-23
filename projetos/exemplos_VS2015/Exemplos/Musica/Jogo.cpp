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

	//	1) Carregar as músicas
	gRecursos.carregarMusica("musica1", "assets/musica/Strut.ogg");
	gRecursos.carregarMusica("musica2", "assets/musica/loop.ogg");
	gRecursos.carregarMusica("musica3", "assets/musica/Codename Granny II.ogg");
}

void Jogo::finalizar()
{
	//	3) Descarregar as músicas
	gRecursos.descarregarTodasMusicas();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		if (gTeclado.pressionou[TECLA_1])
			//	2)	Tocar a música
			gMusica.tocar("musica1", false);

		if (gTeclado.pressionou[TECLA_2])
			//	2)	Tocar a música
			gMusica.tocar("musica2", true);

		if (gTeclado.pressionou[TECLA_3])
			//	2)	Tocar a música
			gMusica.tocar("musica3", false, 3.0f);


		if (gTeclado.pressionou[TECLA_P])
			gMusica.pausar();		//	pausar
		
		if (gTeclado.pressionou[TECLA_C])
			gMusica.continuar();	//	continuar

		if (gTeclado.pressionou[TECLA_S])
			gMusica.parar();		//	parar imediatamente

		if (gTeclado.pressionou[TECLA_F])
			gMusica.parar(3.0f);	//	parar com fade out


		//	Desenhar instruções
		desenharInstrucoes();

		uniTerminarFrame();
	}
}

void Jogo::desenharInstrucoes()
{
	string txt = "Instruções:\n"
		"    Pressione [1] para tocar a música 1 (uma vez).\n"
		"    Pressione [2] para tocar a música 2 (infinitamente).\n"
		"    Pressione [3] para tocar a música 3 (uma vez com fade in de 3 segundos).\n"
		"    Pressione [P] para pausar.\n"
		"    Pressione [C] para continuar.\n"
		"    Pressione [S] para parar de tocar.\n"
		"    Pressione [F] para parar de tocar com fade out de 3 segundo.";

	gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
}