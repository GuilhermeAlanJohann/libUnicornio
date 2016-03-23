#include "Player.h"

Player::Player()
{
	indiceJoystick = 0;
}

Player::~Player()
{
}

void Player::setPos(float x, float y)
{
	personagem.setPos(x, y);
}

void Player::setSpriteSheet(string sheet)
{
	personagem.setSpriteSheet(sheet);
}

void Player::setJoystick(int indice)
{
	indiceJoystick = indice;
}

void Player::atualizar()
{
	personagem.animar();

	//	3.1) Mover o personagem com base na informação dos eixos 'x' e 'y' do joystick
	personagem.mover(gJoysticks[indiceJoystick].x, gJoysticks[indiceJoystick].y);
}

void Player::desenhar()
{
	personagem.desenhar();
}