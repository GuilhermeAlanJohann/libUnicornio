#ifndef UNI_OBJETOTILEMAP_H
#define UNI_OBJETOTILEMAP_H

#include "uniAPI.h"
#include "Sprite.h"
#include "Tile.h"
#include <map>

class CamadaDeObjetosTileMap;
class TileMap;

class UNI_API ObjetoTileMap
{
public:
	ObjetoTileMap();
	virtual ~ObjetoTileMap();

	bool operator==(const ObjetoTileMap &outro);
	bool operator!=(const ObjetoTileMap &outro);

	Sprite *getSprite();
	bool estaVisivel();

	string getNome();
	string getTipo();
	NivelTile getNivel();

	float getX();
	float getY();
	float getRot();
	Vetor2D getPos();

	float getXCentro();
	float getYCentro();
	Vetor2D getPosCentro();

	float getLargura();
	float getAltura();

	void* getPtr();

	CamadaDeObjetosTileMap *getCamada();
	TileMap *getTileMap();

	string getPropriedade(string nome);

	void obterPos(float &x, float &y);
	void obterPosCentro(float &x, float &y);
	void obterTamanho(float &larg, float &alt);

	void setSprite(Sprite *spr);
	void setVisivel(bool b);

	void setNome(string nome);
	void setTipo(string tipo);
	void setNivel(NivelTile nivel);

	void setX(float x);
	void setY(float y);
	void setPos(Vetor2D pos);
	void setPos(float x, float y);
	void setRot(float rot);

	void setXCentro(float x);
	void setYCentro(float y);
	void setPosCentro(const Vetor2D& pos);
	void setPosCentro(float x, float y);

	void setLargura(float larg);
	void setAltura(float alt);
	void setTamanho(const Vetor2D& tam);
	void setTamanho(float larg, float alt);

	void setPtr(void *ptr);

	void setCamada(CamadaDeObjetosTileMap *camada);

	void setPropriedade(string nome, string valor);

	virtual void desenhar(int px, int py);

	//	uso interno
	int _indiceNaCamada;

protected:
	bool visivel;

	string nome;
	string tipo;
	NivelTile nivel;

	float x, y, rot;
	float larg, alt;

	void* voidPtr;

	CamadaDeObjetosTileMap *camada;

	map<string, string>* propriedades;

private:
	Sprite *spr;
};

#endif