#ifndef UNI_BOTAOSPRITE_H
#define UNI_BOTAOSPRITE_H

#include "Sprite.h"

enum EstadoBotaoInterface
{
	BOTAO_INTERFACE_NORMAL,
	BOTAO_INTERFACE_MOUSE_EM_CIMA,
	BOTAO_INTERFACE_ABAIXADO,
	NUMERO_DE_ESTADOS_BOTAO_INTERFACE
};

class BotaoSprite
{
public:
	BotaoSprite();
	~BotaoSprite();

	void inicializar(SpriteSheet* spritesheet);
	void finalizar();

	void atualizar();
	void desenhar();

	bool clicou();

	void setX(float x);
	void setY(float y);
	void setPos(float x, float y);

	float getX();
	float getY();
	void obterPos(float& x, float& y);

	EstadoBotaoInterface getEstado();

	Sprite* getSprite();

private:
	void atualizarEstado();
	bool estaDentroDoRetangulo(int x, int y);

	float x, y;
	bool clique;

	Sprite* spr;
	EstadoBotaoInterface estado;
};

#endif