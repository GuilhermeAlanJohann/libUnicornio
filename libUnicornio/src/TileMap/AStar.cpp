#include "AStar.h"
#include <algorithm>
#include "libUnicornio.h"

AStar::AStar()
{
	mapa = NULL;
	largura_em_tiles = 0;
	altura_em_tiles = 0;

	heuristica = HEURISTICA_MANHATTAN;

	origem.x = 0.0f;
	origem.y = 0.0f;
	destino.x = 0.0f;
	destino.y = 0.0f;

	custoLateral = 10;
	custoDiagonal = 14;

	mover_na_diagonal = false;
	evitar_diagonais_fechadas = false;

	achouCaminho = false;
}

AStar::~AStar()
{
}

TileMap* AStar::getTileMap()
{
	return mapa;
}

void AStar::inicializar(TileMap* mapa)
{
	this->mapa = mapa;
	largura_em_tiles = mapa->getLarguraEmTiles();
	altura_em_tiles = mapa->getAlturaEmTiles();

	int larg_tile = mapa->getLarguraTile();
	int alt_tile = mapa->getAlturaTile();

	grade.resize(largura_em_tiles);
	for(int i = 0; i < largura_em_tiles; ++i)
		grade[i].resize(altura_em_tiles);

	int num_camadas = mapa->getNumLayers();

	for(int i = 0; i < largura_em_tiles; ++i)
		for(int j = 0; j < altura_em_tiles; ++j)
		{
			grade[i][j].custoAdicional = mapa->getCustoAdicionalNoTile(i, j);
			grade[i][j].pos.x = (float)i;
			grade[i][j].pos.y = (float)j;

			if(grade[i][j].caminhavel)
				grade[i][j].caminhavel = mapa->tileECaminhavel(i, j);
		}	
}

void AStar::finalizar()
{
	limparCaminho();
	for(int i = 0; i < largura_em_tiles; ++i)
		grade[i].clear();

	grade.clear();
}

bool AStar::calcularCaminho(Vetor2D origem, Vetor2D destino)
{
	//	valida posicoes de inicio e fim
	if((origem.x < 0.0f) || (origem.x >= largura_em_tiles) 
	|| (origem.y < 0.0f) || (origem.y >= altura_em_tiles)) 
		return false;

	if((destino.x < 0.0f) || (destino.x >= largura_em_tiles)
	|| (destino.y < 0.0f) || (destino.y >= altura_em_tiles))
		return false;

	//	inicializa as etruturas de dados
	limparCaminho();

	//	seta origem e destino
	this->origem = origem;
	this->destino = destino;

	//	se os tiles de origem ou de destino nao forem caminhaveis retorna falso
	if(!grade[origem.x][origem.y].caminhavel || !grade[destino.x][destino.y].caminhavel)
		return false;

	//	coloca o primeiro nodo/tile na lista aberta
	NodoAStar* nodo = &grade[origem.x][origem.y];
	nodo->anterior = NULL;
	nodo->custoH = calcularHeuristica(origem, destino);
	nodo->custoG = 0;
	nodo->custoF = nodo->custoG + nodo->custoH;
	nodo->estaNaListaAberta = true;
	listaAberta.push_back(nodo);

	//	executa a busca passo a passo
	while(!executarUmPasso())
		if(listaAberta.empty()) 
			return false;

	//	pega caminho
	if(achouCaminho)
	{
		for(NodoAStar* nodo = &grade[destino.x][destino.y]; nodo; nodo = nodo->anterior)
			caminho.push_back(*nodo);

		int size = caminho.size();
		for(int i = 0; i < size/2; ++i)
		{
			NodoAStar temp = caminho[i];
			caminho[i] = caminho[size-i-1];
			caminho[size-i-1] = temp;
		}
	}

	return achouCaminho;
}	

bool AStar::calcularCaminho(float origem_x, float origem_y, float destino_x, float destino_y)
{
	return calcularCaminho(Vetor2D(origem_x, origem_y), Vetor2D(destino_x, destino_y));
}

int AStar::calcularHeuristica(Vetor2D origem, Vetor2D destino)
{
	return calcularHeuristica(origem.x, origem.y, destino.x, destino.y);
}

int AStar::calcularHeuristica(float origem_x, float origem_y, float destino_x, float destino_y)
{
	switch(heuristica)
	{
		default:
		case HEURISTICA_MANHATTAN:  
			return ( custoLateral * (abs(origem_x-destino_x) + abs(origem_y-destino_y)) );

		case HEURISTICA_EUCLIDEANA: 
			return ( custoLateral * sqrt(pow(origem_x-destino_x,2.0) + pow(origem_y-destino_y,2.0)) );

		case HEURISTICA_DIAGONAL:
		{
			int h_diagonal = min(abs(origem_x-destino_x), abs(origem_y-destino_y));
			int h_straight = (abs(origem_x-destino_x) + abs(origem_y-destino_y));
			return custoDiagonal * h_diagonal + custoLateral * (h_straight - 2*h_diagonal);
		}

		case HEURISTICA_CRUZ:
		{
			int heu = custoLateral * (abs(origem_x-destino_x) + abs(origem_y-destino_y));
			int cross = abs((origem_x - destino_x)*(this->origem.y - destino_y) - (this->origem.x - destino_x)*(origem_y - destino_y));
			return (heu + cross)/2.0;
		}
	}
}

vector<NodoAStar> AStar::getCaminho()
{
	return caminho;
}

void AStar::desenharCaminho(int r, int g, int b, int a, bool desenharPonterioAnterior)
{
	for(int i = 0; i < caminho.size(); ++i)
		desenharNodo(&caminho[i], r, g, b, a, desenharPonterioAnterior);
}

void AStar::desenharListaAberta(int r, int g, int b, int a, bool desenharPonterioAnterior)
{
	for(int i = 0; i < listaAberta.size(); ++i)
		desenharNodo(listaAberta[i], r, g, b, a, desenharPonterioAnterior);
}

void AStar::desenharListaFechada(int r, int g, int b, int a, bool desenharPonterioAnterior)
{
	for(int i = 0; i < listaFechada.size(); ++i)
		desenharNodo(listaFechada[i], r, g, b, a, desenharPonterioAnterior);
}

void AStar::desenharNodo(NodoAStar* nodo, int r, int g, int b, int a, bool desenharPonterioAnterior)
{
	SDL_Rect rect;
	mapa->tileParaTela((int)nodo->pos.x, (int)nodo->pos.y, rect.x, rect.y);
	rect.w = mapa->getLarguraTile();
	rect.h = mapa->getAlturaTile();

	SDL_SetRenderDrawColor(renderer, r, g, b, 64);
	SDL_RenderFillRect(renderer, &rect);

	if(desenharPonterioAnterior)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, rect.x + rect.w/2, rect.y + rect.h/2, rect.x + rect.w/2 + nodo->posRelativa.x*(-rect.w/2), rect.y + rect.h/2 + nodo->posRelativa.y*(-rect.h/2));
	}
}

void AStar::setHeuristica(HeuristicaAStar heuristica)
{
	this->heuristica = heuristica;
}

void AStar::setMoverNaDiagonal(bool b)
{
	mover_na_diagonal = b;
}

void AStar::setEvitarDiagonaisFechadas(bool b)
{
	evitar_diagonais_fechadas = b;
}

HeuristicaAStar AStar::getHeuristica()
{
	return heuristica;
}

bool AStar::getMoverNaDiagonal()
{
	return mover_na_diagonal;
}

bool AStar::getEvitarDiagonaisFechadas()
{
	return evitar_diagonais_fechadas;
}

NodoAStar* AStar::getNodo(int nodo_x, int nodo_y)
{
	if(nodo_x < 0 || nodo_x >= largura_em_tiles || nodo_y < 0 || nodo_y >= altura_em_tiles)
		return NULL;

	return &grade[nodo_x][nodo_y];
}

void AStar::limparCaminho()
{
	for(int i = 0; i < listaAberta.size(); ++i)
		listaAberta[i]->estaNaListaAberta = false;
	listaAberta.clear();

	for(int i = 0; i < listaFechada.size(); ++i)
		listaFechada[i]->estaNaListaFechada = false;
	listaFechada.clear();

	caminho.clear();
	achouCaminho = false;
}

bool AStar::executarUmPasso()
{
	NodoAStar* nodoAtual = processarNodoComMenorCustoF();
	if((!achouCaminho) && (nodoAtual))
	{
		processarAdjacentes(nodoAtual);
		return false;
	}
	else
		return true;
}

NodoAStar* AStar::processarNodoComMenorCustoF()
{
	if(listaAberta.empty()) 
		return false; 

	int menorF;
	vector<NodoAStar*>::iterator itMenorF;
	vector<NodoAStar*>::iterator it;
	it = listaAberta.begin();
	
	NodoAStar* nodo = (*it);
	menorF = nodo->custoF;
	itMenorF = it;
	it++;
	
	while(it != listaAberta.end())
	{
		if((*it)->custoF < menorF)
		{
			nodo = (*it);
			menorF = nodo->custoF;
			itMenorF = it;
			
		}
		it++;
	}
	listaAberta.erase(itMenorF);
	nodo->estaNaListaAberta = false;

	listaFechada.push_back(nodo);
	nodo->estaNaListaFechada = true;

	if(((int)nodo->pos.x == (int)destino.x) && ((int)nodo->pos.y == (int)destino.y)) 
		achouCaminho = true;

	return nodo;
}

void AStar::processarAdjacentes(NodoAStar* nodoAtual)
{
	float adx, ady;
	int G;
	float ax = nodoAtual->pos.x;
	float ay = nodoAtual->pos.y;

	if(mover_na_diagonal)
		G = custoDiagonal + nodoAtual->custoAdicional;
	else
		G = custoLateral + nodoAtual->custoAdicional;

	adx = ax; ady = ay-1.0f; /*G = C;*/
	processarAdjacente(adx, ady, G, nodoAtual);

	adx = ax+1.0f; ady = ay; /*G = C;*/
	processarAdjacente(adx, ady, G, nodoAtual);
	
	adx = ax; ady = ay+1.0f; /*G = C;*/
	processarAdjacente(adx, ady, G, nodoAtual);
	
	adx = ax-1.0f; ady = ay; /*G = C;*/
	processarAdjacente(adx, ady, G, nodoAtual);

	if(mover_na_diagonal)
	{
		adx = ax-1.0f; ady = ay-1.0f; /*G = CD;*/
		processarAdjacente(adx, ady, G, nodoAtual);
		
		adx = ax+1.0f; ady = ay-1.0f; /*G = CD;*/
		processarAdjacente(adx, ady, G, nodoAtual);

		adx = ax+1.0f; ady = ay+1.0f; /*G = CD;*/
		processarAdjacente(adx, ady, G, nodoAtual);
		
		adx = ax-1.0f; ady = ay+1.0f; /*G = CD;*/
		processarAdjacente(adx, ady, G, nodoAtual);
	}
}

void AStar::processarAdjacente(float adx, float ady, int custoG, NodoAStar* nodoAtual)
{
	if((adx < 0.0f) || (adx >= (float)largura_em_tiles) || (ady < 0.0f) || (ady >= (float)altura_em_tiles))
		return;
	
	if(!evitarDiagonaisFechadas(nodoAtual->pos.x, nodoAtual->pos.y, adx, ady))
	{
		NodoAStar* nodoAdjacente = &grade[adx][ady];
		custoG = (custoG + nodoAtual->custoG) + grade[adx][ady].custoAdicional;
		if(nodoAdjacente->caminhavel && !nodoAdjacente->estaNaListaFechada)
		{
			if(!nodoAdjacente->estaNaListaAberta)
			{
				nodoAdjacente->anterior = nodoAtual;
				nodoAdjacente->custoG = custoG;
				nodoAdjacente->custoH = calcularHeuristica(adx, ady, destino.x, destino.y);
				nodoAdjacente->custoF = nodoAdjacente->custoH + custoG;
				nodoAdjacente->posRelativa = nodoAdjacente->pos - nodoAtual->pos;
				nodoAdjacente->estaNaListaAberta = true;
				listaAberta.push_back(nodoAdjacente);
			}
			else if(custoG < nodoAdjacente->custoG)
			{
				nodoAdjacente->anterior = nodoAtual;
				nodoAdjacente->custoG = custoG;				
				nodoAdjacente->custoF = nodoAdjacente->custoH + custoG;
				nodoAdjacente->posRelativa = nodoAdjacente->pos - nodoAtual->pos;
			}
		}
	}
}

bool AStar::evitarDiagonaisFechadas(float atual_x, float atual_y, float adjacente_x, float adjacente_y)
{
	if(!evitar_diagonais_fechadas) 
		return false;

	int ax = (int)atual_x;
	int ay = (int)atual_y;
	int bx = (int)adjacente_x;
	int by = (int)adjacente_y;

	if(bx == ax-1) 
	{
		if(by == ay-1)
			return(!grade[ax-1][ay].caminhavel || !grade[ax][ay-1].caminhavel);

		else if (by == ay+1)
			return(!grade[ax][ay+1].caminhavel || !grade[ax-1][ay].caminhavel);
	}
	else if(bx == ax+1)
	{
		if(by == ay-1)
			return(!grade[ax][ay-1].caminhavel || !grade[ax+1][ay].caminhavel);

		else if(by == ay+1)
			return(!grade[ax+1][ay].caminhavel || !grade[ax][ay+1].caminhavel);
	}

	return false;
}