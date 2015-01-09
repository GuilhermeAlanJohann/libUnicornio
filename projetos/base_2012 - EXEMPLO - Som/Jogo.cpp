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

	//	1)	carregar audio
	recursos.carregarAudio("tiro", "dados/sons/shot.wav");

	//	inicializar arma (olhar passo numero 2 dentro do metodo setAudio)
	arma.setAudio("tiro");
	arma.recarregar(10);
}

void Jogo::finalizar()
{
	//	4)	descarregar audio. 
	recursos.descarregarAudio("tiro");	//	Descarregar individualmente
	//	recursos.descarregarTudo();		//	Ou, descarregar junto com todo o resto

	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	Se pressionou a tecla ENTER
		if(teclado.pressionou[TECLA_ENTER])	
		{
			//	atirar
			arma.atirar();
		}
		//	Se pressionou a tecla ESPACO
		else if(teclado.pressionou[TECLA_ESPACO])	
		{
			//	recarregar
			arma.recarregar(10);
		}


		//	Desenha as intruções na tela
		uniDesenharTexto("Pressione [ENTER] para atirar", 10, 10, 255, 255, 255, false);
		uniDesenharTexto("Pressione [ESPACO] para recarregar", 10, 30, 255, 255, 255, false);
		uniDesenharTexto("Num Tiros Restantes: " + to_string(arma.getNumBalas()), 10, 50, 255, 255, 255, false);

		uniTerminarFrame();
	}
}