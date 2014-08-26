#include "BotaoSprite.h"
#include "libUnicornio.h"

BotaoSprite::BotaoSprite()
{
	x = 0;
	y = 0;
	clique = false;

	spr = NULL;
	estado = BOTAO_INTERFACE_NORMAL;
}

BotaoSprite::~BotaoSprite()
{
}

void BotaoSprite::inicializar(SpriteSheet* spritesheet)
{
	if(spritesheet)
	{
		spr = new Sprite();
		spr->setSpriteSheet(spritesheet);
	}

	estado = BOTAO_INTERFACE_NORMAL;
}

void BotaoSprite::finalizar()
{
	if(spr)
	{
		delete spr;
		spr = NULL;
	}
}

void BotaoSprite::atualizar()
{
	if(spr)
		spr->avancarAnimacao();

	atualizarEstado();
}

void BotaoSprite::desenhar()
{
	spr->desenhar(x, y);
}

bool BotaoSprite::clicou()
{
	return clique;
}

void BotaoSprite::setX(float x)
{
	this->x = x;
}

void BotaoSprite::setY(float y)
{
	this->y = y;
}

void BotaoSprite::setPos(float x, float y)
{
	this->x = x;
	this->y = y;
}

float BotaoSprite::getX()
{
	return x;
}

float BotaoSprite::getY()
{
	return y;
}

EstadoBotaoInterface BotaoSprite::getEstado()
{
	return estado;
}

Sprite* BotaoSprite::getSprite()
{
	return spr;
}

void BotaoSprite::atualizarEstado()
{
	clique = false;

	if(estaDentroDoRetangulo(mouse.x, mouse.y))
	{
		if(mouse.pressionou[BOTAO_ESQ])
		{
			estado = BOTAO_INTERFACE_ABAIXADO;		//	abaixado
		}
		else if(mouse.soltou[BOTAO_ESQ] && estado == BOTAO_INTERFACE_ABAIXADO)
		{
			estado = BOTAO_INTERFACE_NORMAL;		//	normal
			clique = true;
		}
		else if(!(mouse.segurando[BOTAO_ESQ] && estado == BOTAO_INTERFACE_ABAIXADO))
		{
			estado = BOTAO_INTERFACE_MOUSE_EM_CIMA;		// hover
		}
	}
	else
	{
		estado = BOTAO_INTERFACE_NORMAL;
	}

	if(spr)
	{
		if(estado < spr->getSpriteSheet()->getNumAnimacoes())
			spr->setAnimacao(estado);
	}
}

bool BotaoSprite::estaDentroDoRetangulo(int x, int y)
{
	float x0, x1, y0, y1;
	float ax, ay;
	spr->obterAncora(ax, ay);
	x0 = this->x - spr->getLargura()*ax;
	x1 = x0 + spr->getLargura();
	y0 = this->y - spr->getAltura()*ay;
	y1 = y0 + spr->getAltura();

	return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}