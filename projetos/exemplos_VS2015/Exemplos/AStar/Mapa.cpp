#include "Mapa.h"
#include <time.h>


Mapa::Mapa()
{
}

Mapa::~Mapa()
{
}

void Mapa::inicializar(int tilesX, int tilesY, int largTile, int altTile)
{
	tilesEmX = tilesX;
	tilesEmY = tilesY;
	this->largTile = largTile;
	this->altTile = altTile;

	if (tilesX*largTile < gJanela.getLargura())
		esq = (gJanela.getLargura() - (tilesX*largTile))/2;
	else
		esq = 0;

	if (tilesY*altTile < gJanela.getAltura())
		cima = (gJanela.getAltura() - (tilesY*altTile))/2;
	else
		cima = 0;

	//	1) Inicializar A*
	astar.inicializar(tilesEmX, tilesEmY);

	//	2) Criar obstaculos.
	//		Até 8 obstaculos em posições aleatórias
	uniRandSetSemente(time(NULL));
	for (int i = 0; i < 8; ++i)
	{
		Vetor2D p = uniRandEntre(Vetor2D(0, 0), Vetor2D(tilesEmX - 1, tilesEmY - 1));
		astar.getNodo(p.x, p.y)->caminhavel = false;
	}

	//	3) Inicializar personagem
	personagem.inicializar(this);
}

void Mapa::finalizar()
{
	//	7) Finalizar A*
	astar.finalizar();
}

void Mapa::atualizar()
{
	//	4) Atualizar lógica do personagem
	personagem.atualizar();
}

void Mapa::desenhar()
{
	//	5) Desenhar mapa
	Quad retan;
	retan.larg = largTile-1;
	retan.alt = altTile-1;
	for (int i = 0; i < tilesEmX; ++i)
		for (int j = 0; j < tilesEmY; ++j)
		{
			retan.x = esq +  i*largTile;
			retan.y = cima + j*altTile;

			if(astar.getNodo(i, j)->caminhavel)
				//	Desenhar bordas do retangulo (branco)
				gGraficos.desenharRetangulo(retan);
			else
				//	Desenhar retangulo preenchido (vermelho)
				astar.desenharNodo(astar.getNodo(i, j), esq, cima, largTile, altTile, 255, 0, 0, 255, false);
		}

	//	6) Desenhar personagem
	personagem.desenhar();
}

void Mapa::telaParaTile(int x, int y, float& tx, float& ty)
{
	tx = (x - esq)  / (float)(largTile);
	ty = (y - cima) / (float)(altTile);
}

void Mapa::tileParaTela(float tx, float ty, int& x, int& y)
{
	x = esq  + (tx*(float)largTile);
	y = cima + (ty*(float)altTile);
}

void Mapa::centralizar(float tx, float ty)
{
	float larg = largTile*tilesEmX;
	float alt  =  altTile*tilesEmY;

	esq = tx - larg / 2;
	cima = ty - alt  / 2;
}

AStar* Mapa::getAStar()
{
	return &astar;
}

int Mapa::getTilesEmX()
{
	return tilesEmX;
}

int Mapa::getTilesEmY()
{
	return tilesEmY;
}