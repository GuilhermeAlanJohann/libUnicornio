#ifndef UNI_TILE_H
#define UNI_TILE_H

#include "TileSet.h"

enum ProfundidadeTile
{
	ABAIXO_DOS_OBJETOS,
	NO_NIVEL_DOS_OBJETOS,
	ACIMA_DOS_OBJETOS
};

class Tile
{
public:
	Tile();
	~Tile();

	bool eCaminhavel();
	int getCustoAdicional();
	ProfundidadeTile getProfundidade();
	TileSet* getTileSet();

	void setCaminhavel(bool caminhavel);
	void setCustoAdicional(int c);
	void setProfundidade(ProfundidadeTile profundidade);
	void setTileset(TileSet* tileset);

private:
	TileSet* tileset;

	bool caminhavel;
	ProfundidadeTile profundidade;

	int custoAdicional;	//	informacao para AStar
};

#endif