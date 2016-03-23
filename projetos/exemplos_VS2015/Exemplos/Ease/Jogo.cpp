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
	gRecursos.carregarSpriteSheet("bird", "assets/ease/bird.png", 1, 4);
	//	Mudar cor de fundo
	gJanela.setCorDeFundo(30, 200, 230);

	//	Inicializar o passaro
	passaro.inicializar();
}

void Jogo::finalizar()
{
	//	Descarregar recursos
	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		passaro.atualizar();
		passaro.desenhar();

		desenharInstrucoes();

		uniTerminarFrame();
	}
}

void Jogo::desenharInstrucoes()
{
	string txt = "Instruções:\n"
		"    Clique na tela para mover o pássaro.";

	gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
}