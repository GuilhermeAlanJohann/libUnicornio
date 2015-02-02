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
	BotaoSprite botaoVermelho;
	BotaoSprite botaoVerde;
	BotaoSprite botaoAzul;
};

