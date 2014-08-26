#pragma once
#include "libUnicornio.h"

class Menu
{
public:
	Menu();
	~Menu();

	void inicializar();
	void finalizar();

	void atualizar();
	void desenhar();

private:
	SpriteSheet ssVermelho;
	SpriteSheet ssVerde;
	SpriteSheet ssAzul;

	BotaoSprite botaoVermelho;
	BotaoSprite botaoVerde;
	BotaoSprite botaoAzul;
};

