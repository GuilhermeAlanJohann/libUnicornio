#include "BotaoSprite.h"
#include "Global.h"

BotaoSprite::BotaoSprite()
{
	pos.set(0, 0);
	estado = BOTAOSPRITE_NORMAL;
	clicado = false;
	mudou = false;
	mouse_entrou = false;
	mouse_saiu = false;
	botao_mouse = BOTAO_MOUSE_ESQ;
	for(unsigned int i = 0; i < NUMERO_DE_ESTADOS_BOTAOSPRITE; ++i)
		anims[i] = 0;
}

BotaoSprite::~BotaoSprite()
{
}

bool BotaoSprite::setSpriteSheet(SpriteSheet *spritesheet)
{
	if(!spritesheet)
		return false;

	spr.setSpriteSheet(spritesheet);

	for(unsigned int i = 0; i < NUMERO_DE_ESTADOS_BOTAOSPRITE; ++i)
	{
		if(i < spritesheet->getNumAnimacoes())
			anims[i] = i;
	}

	return true;
}

bool BotaoSprite::setSpriteSheet(string spritesheet)
{
	return setSpriteSheet(gRecursos.getSpriteSheet(spritesheet));
}

void BotaoSprite::atualizar()
{
	atualizar(gTempo.getDeltaTempo());
}

void BotaoSprite::atualizar(double dt)
{
	spr.avancarAnimacao(dt);

	if(estaDentroDoRetangulo(gMouse.x, gMouse.y))
		atualizarEstadoMouse();
	else 
		atualizarEstadoToque();
}

void BotaoSprite::desenhar()
{
	spr.desenhar(pos.x, pos.y);
}

bool BotaoSprite::estaClicado()
{
	return clicado;
}

bool BotaoSprite::estaComMouseEmCima()
{
	return (estado == BOTAOSPRITE_COM_MOUSE_EM_CIMA);
}

bool BotaoSprite::estaAbaixado()
{
	return (estado == BOTAOSPRITE_ABAIXADO);
}
bool BotaoSprite::mudouEstado()
{
	return mudou;
}

bool BotaoSprite::mouseEntrouEmCima()
{
	return mouse_entrou;
}

bool BotaoSprite::mouseSaiuDeCima()
{
	return mouse_saiu;
}

Vetor2D BotaoSprite::getPos()
{
	return pos;
}

float BotaoSprite::getX()
{
	return pos.x;
}

float BotaoSprite::getY()
{
	return pos.y;
}

EstadoBotaoSprite BotaoSprite::getEstado()
{
	return estado;
}

Sprite *BotaoSprite::getSprite()
{
	return &spr;
}

int BotaoSprite::getAnimacaoDoEstado(EstadoBotaoSprite estado)
{
	return anims[estado];
}

int BotaoSprite::getAnimacaoDoEstadoNormal()
{
	return anims[BOTAOSPRITE_NORMAL];
}

int BotaoSprite::getAnimacaoDoEstadoComMouseEmCima()
{
	return anims[BOTAOSPRITE_COM_MOUSE_EM_CIMA];
}

int BotaoSprite::getAnimacaoDoEstadoAbaixado()
{
	return anims[BOTAOSPRITE_ABAIXADO];
}

int BotaoSprite::getBotaoMouse()
{
	return botao_mouse;
}

void BotaoSprite::obterPos(float &x, float &y)
{
	x = pos.x;
	y = pos.y;
}

void BotaoSprite::setPos(Vetor2D pos)
{
	this->pos = pos;
}

void BotaoSprite::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void BotaoSprite::setX(float x)
{
	pos.x = x;
}

void BotaoSprite::setY(float y)
{
	pos.y = y;
}

void BotaoSprite::setEstado(EstadoBotaoSprite estado)
{
	if(this->estado != estado)
		mudou = true;

	this->estado = estado;

	if(anims[estado] < spr.getSpriteSheet()->getNumAnimacoes())
		spr.setAnimacao(anims[estado]);
}

void BotaoSprite::setAnimacaoDoEstado(EstadoBotaoSprite estado, int anim)
{
	anims[estado] = anim;
}

void BotaoSprite::setAnimacaoDoEstadoNormal(int anim)
{
	setAnimacaoDoEstado(BOTAOSPRITE_NORMAL, anim);
}

void BotaoSprite::setAnimacaoDoEstadoComMouseEmCima(int anim)
{
	setAnimacaoDoEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA, anim);
}

void BotaoSprite::setAnimacaoDoEstadoAbaixado(int anim)
{
	setAnimacaoDoEstado(BOTAOSPRITE_ABAIXADO, anim);
}

void BotaoSprite::setBotaoMouse(int botao)
{
	botao_mouse = botao;
}

void BotaoSprite::atualizarEstadoMouse()
{
	clicado = false;
	mudou = false;

	if(estaDentroDoRetangulo(gMouse.x, gMouse.y))
	{
		if(!mouse_entrou)
			mouse_entrou = true;
		mouse_saiu = false;

		if(gMouse.pressionou[botao_mouse])
		{
			setEstado(BOTAOSPRITE_ABAIXADO);
		}
		else if(gMouse.soltou[botao_mouse] && estado == BOTAOSPRITE_ABAIXADO)
		{
			setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);
			clicado = true;
		}
		else if(!(gMouse.segurando[botao_mouse] && estado == BOTAOSPRITE_ABAIXADO))
		{
			setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);
		}
	}
	else
	{
		if(!mouse_saiu)
			mouse_saiu = true;
		mouse_entrou = false;

		setEstado(BOTAOSPRITE_NORMAL);
	}
}

void BotaoSprite::atualizarEstadoToque()
{
	clicado = false;
	mudou = false;

	bool dentro = false;

	Toque t;
	vector<Toque> vetToques = gToques.getTodosToques();
	for(unsigned int i = 0; i < vetToques.size() && !dentro; ++i)
	{
		t = vetToques[i];
		dentro = estaDentroDoRetangulo(t.x, t.y);
	}

	if(dentro)
	{
		if(!mouse_entrou)
			mouse_entrou = true;
		mouse_saiu = false;

		if(t.tipo == TOQUE_PRESSIONOU)
		{
			setEstado(BOTAOSPRITE_ABAIXADO);
		}
		else if(t.tipo == TOQUE_SOLTOU && estado == BOTAOSPRITE_ABAIXADO)
		{
			setEstado(BOTAOSPRITE_NORMAL);
			clicado = true;
		}
		else if(!(t.tipo == TOQUE_SEGURANDO && estado == BOTAOSPRITE_ABAIXADO))
		{
			setEstado(BOTAOSPRITE_NORMAL);
		}
	}
	else
	{
		if(!mouse_saiu)
			mouse_saiu = true;
		mouse_entrou = false;

		setEstado(BOTAOSPRITE_NORMAL);
	}
}

bool BotaoSprite::estaDentroDoRetangulo(int x, int y)
{
	float x0, x1, y0, y1;
	float ax, ay;
	int larg, alt;
	spr.obterAncora(ax, ay);
	spr.obterTamanho(larg, alt);
	x0 = pos.x - larg*ax;
	x1 = x0 + larg;
	y0 = pos.y - alt*ay;
	y1 = y0 + alt;

	return (x >= x0 && x <= x1 && y >= y0 && y <= y1);
}