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

	void inicializar(string sheet, ObjetoTileMap* objeto);

	void atualizar();

	void setDestino(float x, float y);
	bool estaMovendo();

	float getX();
	float getY();

private:
	void atualizarAnimacao();
	void atualizarMovimento();

	ObjetoTileMap* objeto;
	Sprite spr;

	Vetor2D destino;
	Vetor2D inicio;
	float interpolador;
	bool movendo;

	float vel;
};

