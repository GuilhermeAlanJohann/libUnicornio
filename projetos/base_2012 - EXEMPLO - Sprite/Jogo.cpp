#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(800, 600, false);

	//	1)	carregar spritesheet
	//		este método recebe como parametro:
	//			1 - o caminho para a imagem
	//			2 - o número de animacoes
	//			3 - o número de frames da maior animacao
	spritesheet.carregar("dados/imagens/sprite_sheet.png", 5, 4);

	//	setar numero de frames na primeira animacao (porque é um número diferente) 
	spritesheet.setNumFramesAnimacao(0, 1);	//	anim 0, frames = 1


	//	2)	inicializar personagem (setar spritesheet, posicao e velocidade)
	per.setSpriteSheet(&spritesheet);	//	passando um ponteiro!
	per.setPos(res_x/2, res_y/2);		//	bem no meio da tela
	per.setVel(0.4);
}

void Jogo::finalizar()
{
	//	6)	descarregar SpriteSheet
	spritesheet.descarregar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	3)	animar o personagem
		per.animar();

		//	4)	mover o personagem
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

		//	5)	desenhar o personagem
		per.desenhar();


		uniTerminarFrame();
	}
}