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
	bool existeObjetoNaPos(const Vetor2D& pos);
	bool existeObjetoNaPos(float tx, float ty);
	bool existeObjetoNoRetangulo(const Vetor2D& pos, const Vetor2D& tamanho);
	bool existeObjetoNoRetangulo(float tx, float ty, float larg, float alt);
	bool existeObjetoDoTipoNaPos(const string& tipo, const Vetor2D& pos);
	bool existeObjetoDoTipoNaPos(const string& tipo, float tx, float ty);
	bool existeObjetoDoTipoNoRetangulo(const string& tipo, const Vetor2D& pos, const Vetor2D& tamanho);
	bool existeObjetoDoTipoNoRetangulo(const string& tipo, float tx, float ty, float larg, float alt);

	int getNumObjetos();
	ObjetoTileMap *getObjeto(int indice);
	ObjetoTileMap *getObjeto(const string& nome);
	ObjetoTileMap *getObjetoNaPos(const Vetor2D& pos);
	ObjetoTileMap *getObjetoNaPos(float tx, float ty);
	ObjetoTileMap *getObjetoNoRetangulo(const Vetor2D& pos, const Vetor2D& tamanho);
	ObjetoTileMap *getObjetoNoRetangulo(float tx, float ty, float larg, float alt);
	ObjetoTileMap *getObjetoDoTipoNaPos(const string& tipo, const Vetor2D& pos);
	ObjetoTileMap *getObjetoDoTipoNaPos(const string& tipo, float tx, float ty);
	ObjetoTileMap *getObjetoDoTipoNoRetangulo(const string& tipo, const Vetor2D& pos, const Vetor2D& tamanho);
	ObjetoTileMap *getObjetoDoTipoNoRetangulo(const string& tipo, float tx, float ty, float larg, float alt);
	vector<ObjetoTileMap*> getObjetosDoTipo(const string& tipo);
	vector<ObjetoTileMap*> getObjetosNaPos(const Vetor2D& pos);
	vector<ObjetoTileMap*> getObjetosNaPos(float tx, float ty);
	vector<ObjetoTileMap*> getObjetosNoRetangulo(const Vetor2D& pos, const Vetor2D& tamanho);
	vector<ObjetoTileMap*> getObjetosNoRetangulo(float tx, float ty, float larg, float alt);
	vector<ObjetoTileMap*> getObjetosDoTipoNaPos(const string& tipo, const Vetor2D& pos);
	vector<ObjetoTileMap*> getObjetosDoTipoNaPos(const string& tipo, float tx, float ty);
	vector<ObjetoTileMap*> getObjetosDoTipoNoRetangulo(const string& tipo, const Vetor2D& pos, const Vetor2D& tamanho);
	vector<ObjetoTileMap*> getObjetosDoTipoNoRetangulo(const string& tipo, float tx, float ty, float larg, float alt);
	vector<ObjetoTileMap*> getTodosObjetos();

	void setTileMap(TileMap* tilemap);	// uso interno
	TileMap* getTileMap();

private:
	void _obterObjetosNaPos(vector<ObjetoTileMap*>* v, float tx, float ty);
	void _obterObjetosNoRetangulo(vector<ObjetoTileMap*>* v, float tx, float ty, float larg, float alt);
	void _obterObjetosDoTipoNaPos(vector<ObjetoTileMap*>* v, const string& tipo, float tx, float ty);
	void _obterObjetosDoTipoNoRetangulo(vector<ObjetoTileMap*>* v, const string& tipo, float tx, float ty, float larg, float alt);

	string nome;
	bool visivel;
	NivelTile nivel;
	vector<ObjetoTileMap*> objetos;
	TileMap* tilemap;
};

#endif