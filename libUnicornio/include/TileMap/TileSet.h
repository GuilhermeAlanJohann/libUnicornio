#ifndef UNI_TILESET_H
#define UNI_TILESET_H

#include "SDL.h"
#include <string>

using namespace std;

class TileSet
{
public:
	TileSet();
	~TileSet();

	bool carregar(string arquivo, int largura_tiles, int altura_tiles);
	void descarregar();
	bool estaCarregado();
	
	string getNome();

	int getAlturaTiles();
	int getLarguraTiles();

	int getNumTiles();
	int getNumTilesX();
	int getNumTilesY();

	int getPrimeiroIDGlobal();

	void obterTamanhoTiles(int &larg, int &alt);

	SDL_Texture* getTextura();

	void setNome(string nome);
	void setPrimeiroIDGlobal(int primeiro_ID);

private:
	string nome;

	int primeiro_ID_Global;

	int num_tiles_x;
	int num_tiles_y;

	int largura_tile;
	int altura_tile;

	SDL_Texture* tex;
};

#endif