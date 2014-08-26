#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}


void Player::inicializar()
{
	//	carregar spritesheet
	//		este método recebe como parametro:
	//			1 - o caminho para a imagem
	//			2 - o número de frames da maior animacao (celulas em x)
	//			3 - o número de animacoes (celulas em y)
	spritesheet.carregar("dados/imagens/sprite_sheet.png", 4, 5);

	//	setar numero de frames na primeira animacao (porque é um número diferente) 
	spritesheet.setNumFramesAnimacao(0, 1);	//	anim 0, frames = 1


	//	inicializar personagem (setar spritesheet, posicao e velocidade)
	per.setSpriteSheet(&spritesheet);	//	passando um ponteiro!
	per.setPos(res_x/2, res_y/2);		//	bem no meio da tela
	per.setVel(0.4);
}

void Player::finalizar()
{
	//	não precisa fazer nada aqui
}

void Player::atualizar()
{
	//	anima o personagem
	per.animar();

	// move o personagem do player

	if(teclado.segurando[TECLA_DIR])
		per.moverDir();

	else if(teclado.segurando[TECLA_ESQ])
		per.moverEsq();

	else if(teclado.segurando[TECLA_CIMA])
		per.moverCima();

	else if(teclado.segurando[TECLA_BAIXO])
		per.moverBaixo();

	else 
		per.ficarParado();
}

void Player::desenhar()
{
	//	desenha o personagem
	per.desenhar();
}