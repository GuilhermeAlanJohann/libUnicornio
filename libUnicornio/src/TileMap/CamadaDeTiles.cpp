#include "CamadaDeTiles.h"


CamadaDeTiles::CamadaDeTiles()
{
	visivel = true;
}

CamadaDeTiles::~CamadaDeTiles()
{
	idTiles.clear();
}

string CamadaDeTiles::getNome()
{
	return nome;
}

bool CamadaDeTiles::estaVisivel()
{
	return visivel;
}

int CamadaDeTiles::getIDdoTile(int tx, int ty)
{
	return idTiles[tx][ty];
}

void CamadaDeTiles::setNome(string nome)
{
	this->nome = nome;
}

void CamadaDeTiles::setVisivel(bool visivel)
{
	this->visivel = visivel;
}

void CamadaDeTiles::setIDdoTile(int id, int tx, int ty)
{
	idTiles[tx][ty] = id;
}

void CamadaDeTiles::redimensionar(int larg, int alt)
{
	idTiles.resize(larg);
	for(int i = 0; i < larg; ++i)
		idTiles[i].resize(alt);
}