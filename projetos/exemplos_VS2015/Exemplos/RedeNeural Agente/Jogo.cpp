#include "Jogo.h"
#include <random>

Jogo::Jogo()
{
	
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(800, 600, false);

	gRecursos.carregarSpriteSheet("branco", "assets/rede neural/branco.png");

	ambiente.inicializar();

	gDebug.setPos(50, 150);
}

void Jogo::finalizar()
{
	ambiente.finalizar();

	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.pressionou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		ambiente.atualizar();
		ambiente.desenhar();

		desenharInstrucoes();
		
		uniTerminarFrame();
	}
}

void Jogo::desenharInstrucoes()
{
	string txt = "Instruções:\n"
		"Pressione [ENTER] para parar/continuar o treinamento\n"
		"Pressione [D] para desenhar/não desenhar os sensores\n"
		"Pressione [S] para salvar os pesos da rede\n"
		"Pressione [C] para carregar os pesos da rede";

	gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
}