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

	bool tileECaminhavel(float tx, float ty);								//	verifica em todas as camadas se o tile é caminhavel (leva em consideracao tiles de tamanho diferente)
	bool retanguloECaminhavel(float tx, float ty, float larg, float alt);	//	verifica em todas as camadas se o tile é caminhavel (leva em consideracao tiles de tamanho diferente)
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

	CamadaDeObjetosTileMap *criarCamadaDeObjetos(const string& nome);
	bool destruirCamadaDeObjetos(int indice);
	bool destruirCamadaDeObjetos(const string& nome);

	CamadaDeObjetosTileMap *getCamadaDeObjetos(int indice);
	CamadaDeObjetosTileMap *getCamadaDeObjetos(const string& nome);
	CamadaDeTiles *getCamadaDeTiles(int indice);
	CamadaDeTiles *getCamadaDeTiles(const string& nome);
	TileSet *getTileSet(int indice);
	TileSet *getTileSet(const string& nome);
	Tile *getTile(int idGlobal);
	Tile *getTile(const Vetor2D& pos, int indice_camada);
	Tile *getTile(const Vetor2D& pos, const string& nome_camada);
	Tile *getTile(int tx, int ty, int indice_camada);
	Tile *getTile(int tx, int ty, const string& nome_camada);

	bool existeObjetoNaPos(const Vetor2D& pos);
	bool existeObjetoNaPos(float tx, float ty);
	bool existeObjetoNoRetangulo(const Vetor2D& pos, const Vetor2D& tamanho);
	bool existeObjetoNoRetangulo(float tx, float ty, float larg, float alt);
	bool existeObjetoDoTipoNaPos(const string& tipo, const Vetor2D& pos);
	bool existeObjetoDoTipoNaPos(const string& tipo, float tx, float ty);
	bool existeObjetoDoTipoNoRetangulo(const string& tipo, const Vetor2D& pos, const Vetor2D& tamanho);
	bool existeObjetoDoTipoNoRetangulo(const string& tipo, float tx, float ty, float larg, float alt);
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

	string getPropriedade(const string& nome);
	int getPropriedadeInt(const string& nome);
	float getPropriedadeFloat(const string& nome);
	bool getPropriedadeBool(const string& nome);

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
	void setPropriedade(const string& nome, const string& valor);
	void setPropriedadeInt(const string& nome, int valor);
	void setPropriedadeFloat(const string& nome, float valor);
	void setPropriedadeBool(const string& nome, bool valor);

	bool juntarCamadasDeObjetos(int indice_camada1, int indice_camada2);
	bool juntarCamadasDeObjetos(const string& nome_camada1, const string& nome_camada2);
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