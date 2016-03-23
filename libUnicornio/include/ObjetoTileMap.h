#ifndef UNI_OBJETOTILEMAP_H
#define UNI_OBJETOTILEMAP_H

#include "Sprite.h"
#include <map>

class CamadaDeObjetosTileMap;

class ObjetoTileMap
{
public:
	ObjetoTileMap();
	~ObjetoTileMap();

	bool operator==(const ObjetoTileMap &outro);
	bool operator!=(const ObjetoTileMap &outro);

	Sprite *getSprite();
	bool estaVisivel();

	string getNome();
	string getTipo();

	float getX();
	float getY();
	float getRot();
	Vetor2D getPos();

	float getXCentro();
	float getYCentro();
	Vetor2D getPosCentro();

	float getLargura();
	float getAltura();

	void* getDadoDeUsuario();

	CamadaDeObjetosTileMap *getCamada();

	string getPropriedade(string nome);

	void obterPos(float &x, float &y);
	void obterPosCentro(float &x, float &y);
	void obterTamanho(float &larg, float &alt);

	void setSprite(Sprite *spr);
	void setVisivel(bool b);

	void setNome(string nome);
	void setTipo(string tipo);

	void setX(float x);
	void setY(float y);
	void setPos(Vetor2D pos);
	void setPos(float x, float y);
	void setRot(float rot);

	void setXCentro(float x);
	void setYCentro(float y);
	void setPosCentro(Vetor2D pos);
	void setPosCentro(float x, float y);

	void setLargura(float larg);
	void setAltura(float alt);
	void setTamanho(float larg, float alt);

	void setDadoDeUsuario(void *dado);

	void setCamada(CamadaDeObjetosTileMap *camada);

	void setPropriedade(string nome, string valor);

	void desenhar(int px, int py);

protected:
	Sprite *spr;
	bool visivel;

	string nome;
	string tipo;

	float x, y, rot;
	float larg, alt;

	void* dadoDeUsuario;

	CamadaDeObjetosTileMap *camada;

	map<string, string> propriedades;
};

#endif