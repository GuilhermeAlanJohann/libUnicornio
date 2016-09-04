#ifndef UNI_ASTAR_H
#define UNI_ASTAR_H

#include "uniAPI.h"
#include <vector>
#include "NodoAStar.h"
#include "Vetor2D.h"

using namespace std;

class TileMap;

enum UNI_API HeuristicaAStar
{
	HEURISTICA_MANHATTAN,	// padrao
	HEURISTICA_EUCLIDIANA,	// usando distancia euclidiana
	HEURISTICA_DIAGONAL,	// favorece as diagonais
	HEURISTICA_CRUZ			// gera caminhos mais lineares ate o destino
};

class UNI_API AStar
{
public:
	AStar();
	~AStar();

	void inicializar(TileMap* mapa);
	void inicializar(int largura_em_tiles, int altura_em_tiles);
	void finalizar();

	bool calcularCaminho(Vetor2D origem, Vetor2D destino);
	bool calcularCaminho(float origem_x, float origem_y, float destino_x, float destino_y);

	int calcularHeuristica(Vetor2D origem, Vetor2D destino);
	int calcularHeuristica(float origem_x, float origem_y, float destino_x, float destino_y);

	vector<NodoAStar> getCaminho();

	//	funcoes de desenho usando tilemap
	void desenharCaminho(TileMap* tilemap, int r = 0, int g = 255, int b = 0, int a = 64, bool desenharPonterioAnterior = true);
	void desenharListaAberta(TileMap* tilemap, int r = 255, int g = 0, int b = 0, int a = 64, bool desenharPonterioAnterior = true);
	void desenharListaFechada(TileMap* tilemap, int r = 0, int g = 0, int b = 255, int a = 64, bool desenharPonterioAnterior = true);
	void desenharNodo(NodoAStar* nodo, TileMap* tilemap, int r, int g, int b, int a, bool desenharPonterioAnterior = true);

	//	funcoes de desenho sem tilemap
	void desenharCaminho(int px_esq_grade, int py_cima_grade, int larg_tile, int alt_tile, int r = 0, int g = 255, int b = 0, int a = 64, bool desenharPonterioAnterior = true);
	void desenharListaAberta(int px_esq_grade, int py_cima_grade, int larg_tile, int alt_tile, int r = 255, int g = 0, int b = 0, int a = 64, bool desenharPonterioAnterior = true);
	void desenharListaFechada(int px_esq_grade, int py_cima_grade, int larg_tile, int alt_tile, int r = 0, int g = 0, int b = 255, int a = 64, bool desenharPonterioAnterior = true);
	void desenharNodo(NodoAStar* nodo, int px_esq_grade, int py_cima_grade, int larg_tile, int alt_tile, int r, int g, int b, int a, bool desenharPonterioAnterior = true);

	void setHeuristica(HeuristicaAStar heuristica);
	void setMoverNaDiagonal(bool b);
	void setEvitarDiagonaisFechadas(bool b);

	HeuristicaAStar getHeuristica();
	bool getMoverNaDiagonal();
	bool getEvitarDiagonaisFechadas();

	NodoAStar* getNodo(int nodo_x, int nodo_y);

private:
	void limparCaminho();

	bool executarUmPasso();
	NodoAStar* processarNodoComMenorCustoF();	//	pega o nodo com menor custoF da lista aberta e poe na lista fechada

	void processarAdjacentes(NodoAStar* nodoAtual);
	void processarAdjacente(float adx, float ady, int custoG, NodoAStar* nodoAtual);

	bool evitarDiagonaisFechadas(float atual_x, float atual_y, float adjacente_x, float adjacente_y);

	int largura_em_tiles;
	int altura_em_tiles;

	vector<vector<NodoAStar> > grade;

	HeuristicaAStar heuristica;
	vector<NodoAStar*> listaAberta;
	vector<NodoAStar*> listaFechada;
	vector<NodoAStar> caminho;
	int custoLateral;
	int custoDiagonal;

	Vetor2D origem;
	Vetor2D destino;

	bool mover_na_diagonal;
	bool evitar_diagonais_fechadas;

	bool achouCaminho;
};

#endif