#pragma once
#include "Personagem.h"

enum NumeroPlayer
{
	PLAYER_1,
	PLAYER_2,
	PLAYER_3,
	PLAYER_4,
	MAXIMO_DE_PLAYERS
};

class Player
{
public:
	Player();
	~Player();

	void setPos(float x, float y);
	void setSpriteSheet(string sheet);
	void setJoystick(int indice);

	void atualizar();
	void desenhar();

private:
	int indiceJoystick;
	Personagem personagem;
};

