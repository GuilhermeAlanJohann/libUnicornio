#ifndef UNI_OBJETOTILE_H
#define UNI_OBJETOTILE_H

#include "Sprite.h"
#include <map>

class ObjetoTile
{
public:
	ObjetoTile();
	~ObjetoTile();

	bool operator==(const ObjetoTile& other);
	bool operator!=(const ObjetoTile& other);

	Sprite* getSprite();
	bool estaVisivel();

	string getNome();
	string getTipo();

	float getX();
	float getY();
	float getRot();

	float getXCentro();
	float getYCentro();

	float getLargura();
	float getAltura();

	string getPropriedade(string nome);

	void obterPos(float& x, float& y);
	void obterPosCentro(float& x, float& y);
	void obterTamanho(float& larg, float& alt);

	void setSprite(Sprite* spr);
	void setVisivel(bool b);

	void setNome(string nome);
	void setTipo(string tipo);

	void setX(float x);
	void setY(float y);
	void setPos(float x, float y);
	void setRot(float rot);

	void setXCentro(float x);
	void setYCentro(float y);
	void setPosCentro(float x, float y);

	void setLargura(float larg);
	void setAltura(float alt);
	void setTamanho(float larg, float alt);

	void setPropriedade(string nome, string valor);

	void desenhar(int px, int py);

private:
	Sprite* spr;
	bool visivel;

	string nome;
	string tipo;

	float x, y, rot;
	float larg, alt;

	map<string, string> propriedades;
};

#endif