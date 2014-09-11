#pragma once
#include "libUnicornio.h"

enum AnimacaoPersonagem
{
	ANIMACAO_BAIXO,
	ANIMACAO_ESQ,
	ANIMACAO_DIR,
	ANIMACAO_CIMA
};

class Personagem
{
public:
	Personagem();
	~Personagem();

	void inicializar(SpriteSheet* sheet, ObjetoTile* objeto);

	void atualizar();

	void moverPara(float x, float y);
	bool estaMovendo();

	float getX();
	float getY();

private:
	ObjetoTile* objeto;
	Sprite spr;

	float proximo_x;
	float proximo_y;
	float x_anterior;
	float y_anterior;
	float interpolador;
	bool movendo;

	float vel;
};

