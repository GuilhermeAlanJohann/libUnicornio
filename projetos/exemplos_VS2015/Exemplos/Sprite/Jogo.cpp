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
	
	//	1)	Carregar spritesheet.
	//		Este método recebe como parâmetro:
	//			1 - um nome qualquer para o spritesheet
	//			2 - o caminho para a imagem
	//			3 - o número de animacoes
	//			4 - o número de frames da maior animacao
	gRecursos.carregarSpriteSheet("player", "assets/sprite/sprite_sheet.png", 5, 4);

	//	(Opcional) setar numero de frames na primeira animacao (porque é um número diferente) 
	gRecursos.getSpriteSheet("player")->setNumFramesDaAnimacao(0, 1);	//	anim 0, frames = 1

	//	(Opcional) criar mais uma animacao. GIRANDO.
	int anim = gRecursos.getSpriteSheet("player")->adicionarAnimacao(0, 124, 70, 124);		//	passa as coordenadas do primeiro frame como parâmetro
	gRecursos.getSpriteSheet("player")->adicionarFrameNaAnimacao(anim, 0, 124*2, 70, 124);	//	passa as coordenadas do próximo frame como parâmetro
	gRecursos.getSpriteSheet("player")->adicionarFrameNaAnimacao(anim, 0, 124*4, 70, 124);	//	passa as coordenadas do próximo frame como parâmetro
	gRecursos.getSpriteSheet("player")->adicionarFrameNaAnimacao(anim, 0, 124*3, 70, 124);	//	passa as coordenadas do próximo frame como parâmetro


	//	2)	inicializar personagem (setar spritesheet, posicao e velocidade)
	per.setSpriteSheet("player");									//	passando o nome dado ao spritesheet!
	per.setPos(gJanela.getLargura() / 2, gJanela.getAltura() / 2);	//	bem no meio da tela
	per.setVel(0.4);
}

void Jogo::finalizar()
{
	//	6)	descarregar spritesheet
	gRecursos.descarregarSpriteSheet("player");	//	Descarregar individualmente
	//gRecursos.descarregarTudo();				//	Ou descarregar tudo junto, (SpriteSheets, Fontes, Audios)

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	3)	animar o personagem
		per.animar();

		//	4)	mover o personagem e trocar animação
		if(gTeclado.segurando[TECLA_DIR])
			per.moverDir();
		else if(gTeclado.segurando[TECLA_ESQ])
			per.moverEsq();
		else if(gTeclado.segurando[TECLA_CIMA])
			per.moverCima();
		else if(gTeclado.segurando[TECLA_BAIXO])
			per.moverBaixo();
		else if(gTeclado.segurando[TECLA_G])
			per.girar();
		else
			per.ficarParado();

		//	5)	desenhar o personagem
		per.desenhar();


		//	Desenhar instruções
		desenharInstrucoes();

		uniTerminarFrame();
	}
}

void Jogo::desenharInstrucoes()
{
	string txt = "Instruções:\n"
		"    Pressione [DIR] para mover para direita\n"
		"    Pressione [ESQ] para mover para esquerda\n"
		"    Pressione [CIMA] para mover para cima\n"
		"    Pressione [BAIXO] para mover para baixo\n"
		"    Pressione [G] para girar";

	gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
}