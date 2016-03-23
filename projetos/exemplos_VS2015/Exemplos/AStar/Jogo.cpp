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

	//	Carregar recursos 
	gRecursos.carregarSpriteSheet("player", "assets/astar/jelly.png");

	//	Inicializar mapa
	mapa.inicializar(8, 6, 100, 100);
}

void Jogo::finalizar()
{
	//	Finalizar mapa
	mapa.finalizar();

	//	Descarregar recursos
	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	Atualizar mapa
		mapa.atualizar();

		//	Desenhar mapa
		mapa.desenhar();

		//	Desenhar instruções
		desenharInstrucoes();

		uniTerminarFrame();
	}
}

void Jogo::desenharInstrucoes()
{
	string txt = "Instruções:\n"
		"    Clique na tela para mover o personagem.";

	gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
}