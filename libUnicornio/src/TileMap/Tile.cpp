#include "Tile.h"

Tile::Tile()
{
	tileset = NULL;

	caminhavel = true;
	profundidade = ABAIXO_DOS_OBJETOS;

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

ProfundidadeTile Tile::getProfundidade()
{
	return profundidade;
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

void Tile::setProfundidade(ProfundidadeTile profundidade)
{
	this->profundidade = profundidade;
}

void Tile::setTileset(TileSet* tileset)
{
	this->tileset = tileset;
}