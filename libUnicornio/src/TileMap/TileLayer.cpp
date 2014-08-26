#include "TileLayer.h"


TileLayer::TileLayer()
{
	visivel = true;
}

TileLayer::~TileLayer()
{
	idTiles.clear();
}

string TileLayer::getNome()
{
	return nome;
}

bool TileLayer::estaVisivel()
{
	return visivel;
}

int TileLayer::getIDdoTile(int tx, int ty)
{
	return idTiles[tx][ty];
}

void TileLayer::setNome(string nome)
{
	this->nome = nome;
}

void TileLayer::setVisivel(bool visivel)
{
	this->visivel = visivel;
}

void TileLayer::setIDdoTile(int id, int tx, int ty)
{
	idTiles[tx][ty] = id;
}

void TileLayer::redimensionar(int larg, int alt)
{
	idTiles.resize(larg);
	for(int i = 0; i < larg; ++i)
		idTiles[i].resize(alt);
}