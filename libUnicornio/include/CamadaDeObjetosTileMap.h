#ifndef UNI_CAMADADEOBJETOSTILEMAP_H
#define UNI_CAMADADEOBJETOSTILEMAP_H

#include "uniAPI.h"
#include <vector>
#include <string>
#include "ObjetoTileMap.h"

using namespace std;

class TileMap;

class UNI_API CamadaDeObjetosTileMap
{
public:
	CamadaDeObjetosTileMap();
	~CamadaDeObjetosTileMap();

	string getNome();
	bool estaVisivel();
	

	void setNome(string nome);
	void setVisivel(bool visivel);

	ObjetoTileMap *criarObjeto();
	ObjetoTileMap *criarObjeto(Vetor2D pos_centro);
	ObjetoTileMap *criarObjeto(float centro_x, float centro_y);
	void adicionarObjeto(ObjetoTileMap* obj);
	bool destruirObjeto(string nome);
	bool destruirObjeto(ObjetoTileMap *obj);
	bool destruirObjeto(int indice);
	void destruirTodosObjetos();
	bool existeObjetoNaPos(Vetor2D pos);
	bool existeObjetoNaPos(float tx, float ty);
	bool existeObjetoDoTipoNaPos(string tipo, Vetor2D pos);
	bool existeObjetoDoTipoNaPos(string tipo, float tx, float ty);

	int getNumObjetos();
	ObjetoTileMap *getObjeto(int indice);
	ObjetoTileMap *getObjeto(string nome);
	ObjetoTileMap *getObjetoNaPos(Vetor2D pos);
	ObjetoTileMap *getObjetoNaPos(float tx, float ty);
	ObjetoTileMap *getObjetoDoTipoNaPos(string tipo, Vetor2D pos);
	ObjetoTileMap *getObjetoDoTipoNaPos(string tipo, float tx, float ty);
	vector<ObjetoTileMap*> getObjetosDoTipo(string tipo);
	vector<ObjetoTileMap*> getObjetosNaPos(Vetor2D pos);
	vector<ObjetoTileMap*> getObjetosNaPos(float tx, float ty);
	vector<ObjetoTileMap*> getObjetosDoTipoNaPos(string tipo, Vetor2D pos);
	vector<ObjetoTileMap*> getObjetosDoTipoNaPos(string tipo, float tx, float ty);
	vector<ObjetoTileMap*> getTodosObjetos();

	void setTileMap(TileMap* tilemap);	// uso interno
	TileMap* getTileMap();

private:
	string nome;
	bool visivel;
	NivelTile nivel;
	vector<ObjetoTileMap*> objetos;
	TileMap* tilemap;
};

#endif