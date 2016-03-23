#include "TelaJogo.h"



TelaJogo::TelaJogo()
{
}

TelaJogo::~TelaJogo()
{
}

void TelaJogo::aoEntrar()
{
	gRecursos.carregarFonte("fonte", "assets/maquina de estados/arial.ttf", 32);

	txt.setFonte("fonte");
	txt.setString("Tela de jogo\nPressione [ENTER] pra voltar");
	txt.setAlinhamento(TEXTO_CENTRALIZADO);
}

void TelaJogo::aoSair()
{
	gRecursos.descarregarFonte("fonte");
}

void TelaJogo::aoAtualizar(float dt)
{
	//	Se terminou o fade out, volta para a tela de anterior (TelaMenu)
	//		O m�todo "desempilharEstado" simplesmente volta para a tela anterior, se n�o houver
	//		uma tela anterior, a maquina fica vazia.
	if (gJanela.fading.terminouFadeOut())
	{
		getMaquinaDeEstadosComPilha()->desempilharEstado();
		return;
	}

	//	Se ainda est� executando o fade in ou fade out, retorna e n�o executa as linhas seguintes
	if (gJanela.fading.estaExecutando())
		return;

	//	Se pressionou a tecla enter, inicia o fade out
	if (gTeclado.pressionou[TECLA_ENTER])
		gJanela.fading.iniciarFadeOut();
}

void TelaJogo::aoDesenhar()
{
	txt.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
}