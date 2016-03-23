#include "Personagem.h"


Personagem::Personagem()
{
	objeto = NULL;
}

Personagem::~Personagem()
{
}

void Personagem::inicializar(string sheet, ObjetoTileMap* objeto)
{
	//	setar spritesheet
	spr.setSpriteSheet(sheet);

	//	setar ancora para os pes do personagem
	spr.setAncora(0.5, 0.75);

	//	set vel anim (4 frames por segundo)
	spr.setVelocidadeAnimacao(4.0);

	//	Guardar o ponteiro do objeto
	this->objeto = objeto;

	//	Setar sprite para o objeto
		//	ao fazer isso, o sprite passa a ser desenhado automaticamente junto com o mapa, na posicao central do objeto, 
		//	entao não precisamos chamar spr.desenhar(x, y)
	objeto->setSprite(&spr);

	//	Setar valores iniciais
	movendo = false;
	inicio.x = objeto->getXCentro();
	inicio.y = objeto->getYCentro();
	destino.x = 0;
	destino.y = 0;
	interpolador = 0.0f;
	vel = 2.0;
}

void Personagem::atualizar()
{
	atualizarAnimacao();
	atualizarMovimento();
}

void Personagem::setDestino(float x, float y)
{
	destino.x = x;
	destino.y = y;
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

void Personagem::atualizarAnimacao()
{
	//	Se está movendo
	if (movendo)
	{
		//	Se está movendo para direita
		if (destino.x - inicio.x > 0.0)
		{
			spr.setAnimacao(ANIMACAO_DIR);	//	setar animação
		}
		//	Se está movendo para esquerda
		else if (destino.x - inicio.x < 0.0)
		{
			spr.setAnimacao(ANIMACAO_ESQ);	//	setar animação
		}
		//	Se está movendo para baixo
		else if (destino.y - inicio.y > 0.0)
		{
			spr.setAnimacao(ANIMACAO_BAIXO); //	setar animação
		}
		//	Se está movendo para cima
		else if (destino.y - inicio.y < 0.0)
		{
			spr.setAnimacao(ANIMACAO_CIMA);	//	setar animação
		}

		//	Avançar anim
		spr.avancarAnimacao();
	}
	else
	{
		//	Se nao esta movendo, mostra o frame 0 (parado) e não avança a animação
		spr.setFrame(0);
	}
}

void Personagem::atualizarMovimento()
{
	if (movendo)
	{
		//	Interpola posições
		float x = inicio.x + (destino.x - inicio.x)*interpolador;
		float y = inicio.y + (destino.y - inicio.y)*interpolador;

		//	Avança interpolação com velocidade de vel (2.0) tiles por segundo;
		interpolador += vel*gTempo.getDeltaTempo();

		//	Se interpolador chegou em, ou ultrapassou 100%,
		if (interpolador >= 1.0)
		{
			interpolador = 0.0f;
			x = destino.x;			//	x = x final
			y = destino.y;			//	y = y final
			inicio.x = destino.x;
			inicio.y = destino.y;
			movendo = false;		// para de mover
		}

		//	Setar posicao atual para o objeto no mapa
		objeto->setPosCentro(x, y);
	}
}