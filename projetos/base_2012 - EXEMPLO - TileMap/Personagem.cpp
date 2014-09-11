#include "Personagem.h"


Personagem::Personagem()
{
	objeto = NULL;
}

Personagem::~Personagem()
{
}

void Personagem::inicializar(SpriteSheet* sheet, ObjetoTile* objeto)
{
	//	setar spritesheet
	spr.setSpriteSheet(sheet);

	//	setar ancora para os pes do personagem
	spr.setAncora(0.5, 0.75);

	//	set vel anim (4 frames por segundo)
	spr.setVelocidadeAnimacao(4.0);

	//	guardar o ponteiro do objeto
	this->objeto = objeto;

	//	setar sprite para o objeto
		//	ao fazer isso, o sprite passa a ser desenhado automaticamente junto com o mapa,na posicao central do objeto, 
		//	entao nao precisamos chamar spr.desenhar(x, y)
	objeto->setSprite(&spr);

	//	setar valores iniciais
	movendo = false;
	x_anterior = objeto->getXCentro();
	y_anterior = objeto->getYCentro();
	proximo_x = 0;
	proximo_y = 0;
	interpolador = 0.0f;
	vel = 1.0;
}

void Personagem::atualizar()
{
	if(movendo)
	{
		//	setar anim
		if(proximo_x - x_anterior > 0.0)
		{
			spr.setAnimacao(ANIMACAO_DIR);
		}
		else if(proximo_x - x_anterior < 0.0)
		{
			spr.setAnimacao(ANIMACAO_ESQ);
		}
		else if(proximo_y - y_anterior > 0.0)
		{
			spr.setAnimacao(ANIMACAO_BAIXO);
		}
		else if(proximo_y - y_anterior < 0.0)
		{
			spr.setAnimacao(ANIMACAO_CIMA);
		}

		//	interpola posicoes
		float x = x_anterior + (proximo_x - x_anterior)*interpolador;
		float y = y_anterior + (proximo_y - y_anterior)*interpolador;

			//	avanca interpolacao com velocidade de vel(1.0) tiles por segundo;
		interpolador += vel*deltaTempo;
		if(interpolador >= 1.0)
		{
			interpolador = 0.0f;
			x = proximo_x;
			y = proximo_y;
			x_anterior = proximo_x;
			y_anterior = proximo_y;
			movendo = false;
		}
			

		//	setar posicao atual para o objeto no mapa
		objeto->setPosCentro(x, y);

		//	avançar anim
		spr.avancarAnimacao();
	}
	else
	{
		//	se nao esta movendo, mostra o frame 0
		spr.setFrame(0);
	}
}

void Personagem::moverPara(float x, float y)
{
	proximo_x = x;
	proximo_y = y;
	movendo = true;
}

bool Personagem::estaMovendo()
{
	return movendo;
}

float Personagem::getX()
{
	return objeto->getXCentro();
}

float Personagem::getY()
{
	return objeto->getYCentro();
}