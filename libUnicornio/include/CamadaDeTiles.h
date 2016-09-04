#ifndef UNI_CAMADADETILES_H
#define UNI_CAMADADETILES_H

#include "uniAPI.h"
#include <vector>
#include <string>
#include <SDL.h>

using namespace std;

class UNI_API CamadaDeTiles
{
public:
	CamadaDeTiles();
	~CamadaDeTiles();

	string getNome();
	bool estaVisivel();
	int getIDdoTile(int tx, int ty);

	void setNome(string nome);
	void setVisivel(bool visivel);
	void setIDdoTile(int id, int tx, int ty);

	void redimensionar(int larg, int alt);

private:
	string nome;
	bool visivel;
	vector<vector<Uint16> > idTiles;
};

#endif