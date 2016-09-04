#ifndef UNI_TILE_H
#define UNI_TILE_H

#include "uniAPI.h"
#include "TileSet.h"

enum UNI_API NivelTile
{
	ABAIXO_DOS_OBJETOS,
	NO_NIVEL_DOS_OBJETOS,
	ACIMA_DOS_OBJETOS
};

class UNI_API Tile
{
public:
	Tile();
	~Tile();

	bool eCaminhavel();
	int getCustoAdicional();
	NivelTile getNivel();
	TileSet* getTileSet();

	void setCaminhavel(bool caminhavel);
	void setCustoAdicional(int c);
	void setNivel(NivelTile nivel);
	void setTileset(TileSet* tileset);

private:
	TileSet* tileset;

	bool caminhavel;
	Uint8 nivel;

	Uint8 custoAdicional;	//	informacao para AStar
};

#endif