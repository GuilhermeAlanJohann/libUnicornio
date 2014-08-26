#ifndef UNI_TILELAYER_H
#define UNI_TILELAYER_H

#include <vector>
#include <string>

using namespace std;

class TileLayer
{
public:
	TileLayer();
	~TileLayer();

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
	vector<vector<int>> idTiles;
};

#endif