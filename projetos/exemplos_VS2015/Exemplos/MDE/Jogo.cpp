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

	gRecursos.carregarSpriteSheet("parado", "assets/maquina de estados/spritesheet_parado.png", 5, 4);
	gRecursos.getSpriteSheet("parado")->juntarTodasAnimacoes();
	gRecursos.carregarSpriteSheet("movendo", "assets/maquina de estados/spritesheet_movendo.png", 5, 4);
	gRecursos.getSpriteSheet("movendo")->juntarTodasAnimacoes();

	//	1)	Inicializar a máquina de estados
	//		Veja como isso é feito dentro do método da classe Agente.
	agente.inicializar();
}

void Jogo::finalizar()
{
	//	3)	Finalizar a máquina de estados
	agente.finalizar();

	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	2) Atualizar a máquina de estados.
		//		É durante este passo que a maquina de 
		//		estados vai trocar de um estado para o outro.
		agente.atualizar();

		//	(Opcional) Desenhar agente.
		//		Uma máquina de estados por si só não é desenhavel.
		//		Mas como estamos usando ela para programar um objeto 
		//		que precisa ser mostrado na tela, precisamos de um
		//		método para desenha-lo.
		agente.desenhar();

		//	Desenhar as instruções 
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