#include "Tile.h"

Tile::Tile()
{
	tileset = NULL;

	caminhavel = true;
	nivel = ABAIXO_DOS_OBJETOS;

	custoAdicional = 0;
}

Tile::~Tile()
{
}

bool Tile::eCaminhavel()
{
	return caminhavel;
}

int Tile::getCustoAdicional()
{
	return custoAdicional;
}

NivelTile Tile::getNivel()
{
	return (NivelTile)nivel;
}

TileSet* Tile::getTileSet()
{
	return tileset;
}

void Tile::setCaminhavel(bool caminhavel)
{
	this->caminhavel = caminhavel;
}

void Tile::setCustoAdicional(int c)
{
	custoAdicional = c;
}

void Tile::setNivel(NivelTile nivel)
{
	this->nivel = nivel;
}

void Tile::setTileset(TileSet* tileset)
{
	this->tileset = tileset;
}