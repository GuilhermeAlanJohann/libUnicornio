#include "TocadorDeSom.h"


TocadorDeSom::TocadorDeSom()
{
}

TocadorDeSom::~TocadorDeSom()
{
}

void TocadorDeSom::inicializar()
{
	som.carregar("dados/sons/shot.wav");
	som.setAngulo(0);		//	angulo (pan/eixo y) de onde vem o som (0 - 360). O padrão é 0 (bem em frente)
	som.setDistancia(0);	//	distancia de onde vem o som. O padrão é 0 (bem no local do som)
	som.setVolume(100);		//	volume do som. O padrão é 128 (máximo);
}

void TocadorDeSom::finalizar()
{}

void TocadorDeSom::atualizar()
{
	//	tocar/parar
	if(teclado.pressionou[TECLA_ENTER])
	{
		if(som.estaTocando())
			som.parar();
		else
			som.tocar();
	}

	//	tocar repeditamente 
	else if(teclado.pressionou[TECLA_ESPACO] && !som.estaTocando())
	{
		som.tocar(true);
	}
}

void TocadorDeSom::desenharInstrucoes()
{
	uniDesenharTexto("Pressione [ENTER] para tocar/parar", 10, 10, 255, 255, 255, false);
	uniDesenharTexto("Pressione [ESPACO] para tocar repetidamente", 10, 25, 255, 255, 255, false);
}