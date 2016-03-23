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

	//	Carregar a fonte para o texto
	gRecursos.carregarFonte("fonte", "assets/comum/arial.ttf", 32);

	//	Inicializar o input de texto
	input.inicializar();
}

void Jogo::finalizar()
{
	//	Finalizar o input de texto
	input.finalizar();

	//	Descarregar todos os recursos (fonte para o texto)
	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	Atualizar e desenhar o input de texto
		input.atualizar();
		input.desenhar();

		//	Desenhar instruções
		desenharInstrucoes();

		uniTerminarFrame();
	}
}

void Jogo::desenharInstrucoes()
{
	string txt = "Instruções:\n"
		"    Digite um texto!\n"
		"    Use as teclas direcionais para mover o cursor.\n"
		"    Segure [SHIFT] e use as teclas direcionais para selecionar parte do texto.\n"
		"    Use as teclas [VOLTAR] ou [DELETE] para apagar o texto.\n"
		"    Experimente usar as teclas [HOME] e [END] para mover o cursor.\n"
		"    Experimente também, digitar um texto com acentos.";

	gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
}