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
	gRecursos.carregarAudio("tiro", "assets/som/shot.wav");

	//	inicializar arma (olhar passo numero 2 dentro do metodo setAudio)
	arma.setAudio("tiro");
	arma.recarregar(10);

	//	(Opcional) Setar volume global. Afeta todos os sons!
	//	O Padrão já é 100.0 (100%, volume máximo).
	gAudios.setVolumeGlobal(100.0);
}

void Jogo::finalizar()
{
	//	4)	descarregar audio. 
	gRecursos.descarregarAudio("tiro");	//	Descarregar individualmente
	//	recursos.descarregarTudo();		//	Ou descarregar junto com todo o resto

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	Se pressionou a tecla ENTER
		if(gTeclado.pressionou[TECLA_ENTER])	
		{
			//	atirar
			arma.atirar();
		}
		//	Se pressionou a tecla ESPACO
		else if(gTeclado.pressionou[TECLA_ESPACO])	
		{
			//	recarregar
			arma.recarregar(10);
		}

		//	Desenha as intruções na tela
		desenharInstrucoes();

		uniTerminarFrame();
	}
}

void Jogo::desenharInstrucoes()
{
	string txt = "Instruções:\n"
		"    Pressione [ENTER] para atirar\n"
		"    Pressione [ESPACO] para recarregar\n"
		"    Número de tiros restantes: " + to_string(arma.getNumBalas());

	gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
}