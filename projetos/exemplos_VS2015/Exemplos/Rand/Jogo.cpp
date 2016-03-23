#include "Jogo.h"
#include <time.h>

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(800, 600, false);

	//	Carregar fonte
	gRecursos.carregarFonte("fonte", "assets/comum/arial.ttf", 46);
	//	Setar fonte e string inicial
	txt.setFonte("fonte");
	txt.setString("0");

	//	1) Seta a semente do rand
	uniRandSetSemente(time(NULL));
}

void Jogo::finalizar()
{
	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		if (gTeclado.pressionou[TECLA_I])
		{
			//	2) Sortear um número (inteiro)
			int i = uniRandEntre(-100, 100);

			//	seta string no texto
			txt.setString(to_string(i));
		}

		if (gTeclado.pressionou[TECLA_F])
		{
			//	2) Sortear um número (float)
			float f = uniRandEntre(-100.0f, 100.0f);

			//	seta string no texto
			txt.setString(to_string(f));
		}

		if (gTeclado.pressionou[TECLA_V])
		{
			//	2) Sortear um número (float)
			Vetor2D v = uniRandEntre(Vetor2D(-100, -100), Vetor2D(100, 100));

			//	seta string no texto
			string s = "(" + to_string(v.x) + ", " + to_string(v.y) + ")";
			txt.setString(s);
		}

		//	Desenhar	
		txt.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

		desenharInstrucoes();

		uniTerminarFrame();
	}
}

void Jogo::desenharInstrucoes()
{
	string txt = "Instrucoes:\n"
		"    Pressione [I] para sortear um número inteiro entre -100 e +100.\n"
		"    Pressione [F] para sortear um número float entre -100.0 e +100.0.\n"
		"    Pressione [V] para sortear um Vetor2D entre (-100, -100) e (+100, +100).";

	gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
}