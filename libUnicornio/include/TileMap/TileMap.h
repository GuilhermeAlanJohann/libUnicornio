#ifndef UNI_TILEMAP_H
#define UNI_TILEMAP_H

#include "TileLayer.h"
#include "TileSet.h"
#include "Tile.h"
#include "ObjetoTile.h"

class TileMap
{
public:
	TileMap();
	~TileMap();

	bool carregar(string arquivo);
	bool carregarConfigTileSet(TileSet* tileset, string arquivo);
	bool carregarConfigTileSet(string nome_tileset, string arquivo);
	void descarregar();
	bool estaCarregado();
	void desenhar();

	ObjetoTile* criarObjeto();
	bool destruirObjeto(string nome);
	bool destruirObjeto(ObjetoTile* obj);
	bool existeObjetoNaPos(float tx, float ty);
	bool existeObjetoDoTipoNaPos(string tipo, float tx, float ty);

	void telaParaTile(int px, int py, float& tx, float& ty);
	void tileParaTela(float tx, float ty, int& px, int& py);

	bool tileECaminhavel(float tx, float ty);			//	verifica em todas as layers se o tile é caminhavel (leva em consideracao tiles de tamanho diferente)
	int getCustoAdicionalNoTile(float tx, float ty);	//	verifica em todas as layers e soma o custo adicional (leva em consideracao tiles de tamanho diferente)

	//	gets
	float getX();
	float getY();
	float getXCentro();
	float getYCentro();

	int getLarguraEmTiles();
	int getAlturaEmTiles();

	int getLarguraTile();
	int getAlturaTile();

	int getNumTilesNaTelaEmX();
	int getNumTilesNaTelaEmY();

	int getNumLayers();
	int getNumTileSets();
	int getNumTiles();
	int getNumObjetos();

	TileLayer* getTileLayer(int indice);
	TileLayer* getTileLayer(string nome);
	TileSet* getTileSet(int indice);
	TileSet* getTileSet(string nome);
	Tile* getTile(int idGlobal);
	Tile* getTile(int tx, int ty, int indiceLayer);
	Tile* getTile(int tx, int ty, string nomeLayer);
	ObjetoTile* getObjeto(int indice);
	ObjetoTile* getObjeto(string nome);
	ObjetoTile* getObjetoNaPos(float tx, float ty);
	ObjetoTile* getObjetoDoTipoNaPos(string tipo, float tx, float ty);
	vector<ObjetoTile*> getObjetosDoTipo(string tipo);
	vector<ObjetoTile*> getObjetosNaPos(float tx, float ty);
	vector<ObjetoTile*> getObjetosDoTipoNaPos(string tipo, float tx, float ty);

	string getPropriedade(string nome);
	int getPropriedadeInt(string nome);
	float getPropriedadeFloat(string nome);
	bool getPropriedadeBool(string nome);

	void obterPos(float& x, float& y);
	void obterPosCentro(float& x, float& y);
	void obterTamanhoEmTiles(int& larg, int& alt);
	void obterTamanhoTile(int& larg, int& alt);

	//	sets
	void setX(float x);
	void setY(float y);
	void setPos(float x, float y);
	void setXCentro(float x);
	void setYCentro(float y);
	void setPosCentro(float x, float y);
	void setPropriedade(string nome, string valor);
	void setPropriedadeInt(string nome, int valor);
	void setPropriedadeFloat(string nome, float valor);
	void setPropriedadeBool(string nome, bool valor);

private:
	void desenharTileNoPixel(int id, float px, float py);
	void ordenarObjetosPorYCentral();

	bool carregou;

	vector<TileLayer> layers;
	vector<TileSet> tilesets;
	vector<Tile> tiles;
	vector<ObjetoTile*> objetos;

	float x;	//	pos x (em tiles) do primeiro tile 
	float y;	//	pos y (em tiles) do primeiro tile 

	float desloc_x;		//	deslocamento do mapa em x (usado para centralizar o mapa quando ele cabe todo na tela)
	float desloc_y;		//	deslocamento do mapa em y (usado para centralizar o mapa quando ele cabe todo na tela)

	int maior_largura_tile;		//	largura do tile com maior largura. medido pelo tileset. (Usado quando existem tilesets com larguras diferentes)
	int maior_altura_tile;		//	altura do tile com maior altura. medido pelo tileset. (Usado quando existem tilesets com alturas diferentes)

	int largura_em_tiles;	//	largura do mapa em tiles
	int altura_em_tiles;	//	altura do mapa em tiles

	int largura_tile;	//	largura de um tile
	int altura_tile;	//	altura de um tile

	map<string, string> propriedades;	//	propriedades do mapa
};

#endif