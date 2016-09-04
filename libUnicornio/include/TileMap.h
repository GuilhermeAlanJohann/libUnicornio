#ifndef UNI_TILEMAP_H
#define UNI_TILEMAP_H

#include "uniAPI.h"
#include "CamadaDeObjetosTileMap.h"
#include "CamadaDeTiles.h"
#include "TileSet.h"
#include "Tile.h"
#include "json/json.h"

class UNI_API TileMap
{
public:
	TileMap();
	~TileMap();

	bool carregar(const string& arquivo);
	bool carregarConfigTileSet(TileSet *tileset, const string& arquivo);
	bool carregarConfigTileSet(const string& nome_tileset, const string& arquivo);
	void descarregar();
	bool estaCarregado();
	void desenhar();

	void telaParaTile(int px, int py, float &tx, float &ty);
	void tileParaTela(float tx, float ty, int &px, int &py);

	bool tileECaminhavel(float tx, float ty);			//	verifica em todas as camadas se o tile é caminhavel (leva em consideracao tiles de tamanho diferente)
	int getCustoAdicionalNoTile(float tx, float ty);	//	verifica em todas as camadas e soma o custo adicional (leva em consideracao tiles de tamanho diferente)

	void adicionarObjetoNaRenderQueue(ObjetoTileMap* obj);	//	não usar! Uso interno.
	void removerObjetoDaRenderQueue(ObjetoTileMap* obj);	//	não usar! Uso interno.

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

	int getNumCamadasDeObjetos();
	int getNumCamadasDeTiles();
	int getNumTileSets();
	int getNumTiles();

	CamadaDeObjetosTileMap *getCamadaDeObjetos(int indice);
	CamadaDeObjetosTileMap *getCamadaDeObjetos(string nome);
	CamadaDeTiles *getCamadaDeTiles(int indice);
	CamadaDeTiles *getCamadaDeTiles(string nome);
	TileSet *getTileSet(int indice);
	TileSet *getTileSet(string nome);
	Tile *getTile(int idGlobal);
	Tile *getTile(Vetor2D pos, int indice_camada);
	Tile *getTile(Vetor2D pos, string nome_camada);
	Tile *getTile(int tx, int ty, int indice_camada);
	Tile *getTile(int tx, int ty, string nome_camada);

	bool existeObjetoNaPos(Vetor2D pos);
	bool existeObjetoNaPos(float tx, float ty);
	bool existeObjetoDoTipoNaPos(string tipo, Vetor2D pos);
	bool existeObjetoDoTipoNaPos(string tipo, float tx, float ty);
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

	bool juntarCamadasDeObjetos(int indice_camada1, int indice_camada2);
	bool juntarCamadasDeObjetos(string nome_camada1, string nome_camada2);
	void juntarTodasCamadasDeObjetos();

protected:
	string acharCaminhoTileSet(const string& caminhoOriginal, const string& caminhoTilemap);
	void desenharTileNoPixel(int id, float px, float py);
	void prepararRenderQueue();
	void limparRenderQueue();
	void quicksortObjetosTileMap(ObjetoTileMap *o, int menor, int maior);

	bool carregou;

	vector<CamadaDeObjetosTileMap*> camadas_objetos;
	vector<CamadaDeTiles> camadas_tiles;
	vector<TileSet> tilesets;
	vector<Tile> tiles;

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


	vector<ObjetoTileMap*> objetosDesenhaveis;
	vector<ObjetoTileMap*> renderQueueObjetos;
	Sint32 finalRenderQueueAbaixo;
	Sint32 finalRenderQueueAoMeio;
};

#endif