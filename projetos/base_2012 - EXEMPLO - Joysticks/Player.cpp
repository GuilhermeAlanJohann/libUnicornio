#include "Player.h"

Player::Player()
{
	joystick = NULL;
}

Player::~Player()
{
}

void Player::setPos(float x, float y)
{
	personagem.setPos(x, y);
}

void Player::setSpriteSheet(SpriteSheet* sheet)
{
	personagem.setSpriteSheet(sheet);
}

void Player::setJoystick(Joystick* joy)
{
	joystick = joy;
}

void Player::atualizar()
{
	//	move o personagem com base na informação dos eixos 'x' e 'y' do joystick
	personagem.mover(joystick->x, joystick->y);
}

void Player::desenhar()
{
	personagem.desenhar();
}