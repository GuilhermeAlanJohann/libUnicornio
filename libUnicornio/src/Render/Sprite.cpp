#include "Sprite.h"
//#include "uniFuncoesPrincipais.h"
#include "Global.h"

Sprite::Sprite()
	:sheet(NULL), frame_atual(0), anim_atual(0), tempo_anim(0.0), vel_anim(2.0f)
{
	ancora.set(0.5f, 0.5f);
	escala.set(1.0f, 1.0f);
	cor.r = 255;
	cor.g = 255;
	cor.b = 255;
	cor.a = 255;
	flags = FLAG_SPRITE_NENHUM;
}

Sprite::Sprite(const Sprite &cp)
{
	sheet = cp.sheet;
	frame_atual = 0;
	anim_atual = 0;
	tempo_anim = cp.tempo_anim;
	vel_anim = cp.vel_anim;
	ancora = cp.ancora;
	escala = cp.escala;
	flags = cp.flags;
	cor = cp.cor;
}

Sprite::~Sprite()
{
	//	nada :)
}

Sprite& Sprite::operator=(const Sprite &r)
{
	if(*this != r)
	{
		sheet = r.sheet;
		frame_atual = r.frame_atual;
		anim_atual = r.anim_atual;
		tempo_anim = r.tempo_anim;
		vel_anim = r.vel_anim;
		ancora = r.ancora;
		escala = r.escala;
		flags = r.flags;
		cor = r.cor;
	}

	return *this;
}

bool Sprite::operator==(const Sprite &r)
{
	return (sheet == r.sheet 
		&& frame_atual == r.frame_atual 
		&& anim_atual == r.anim_atual 
		&& vel_anim == r.vel_anim 
		&& tempo_anim == r.tempo_anim 
		&& ancora == r.ancora 
		&& escala == r.escala
		&& flags == r.flags
		&& cor.r == r.cor.r 
		&& cor.g == r.cor.g 
		&& cor.b == r.cor.b 
		&& cor.a == r.cor.a );
}

bool Sprite::operator!=(const Sprite &r)
{
	return !(*this == r);
}

Vetor2D Sprite::getAncora()
{
	return ancora;
}

float Sprite::getAncoraX()
{
	return ancora.x;
}

float Sprite::getAncoraY()
{
	return ancora.y;
}

Vetor2D Sprite::getEscala()
{
	return escala;
}

float Sprite::getEscalaX()
{
	return escala.x;
}

float Sprite::getEscalaY()
{
	return escala.y;
}

int	Sprite::getLargura()
{
	if (!sheet)
		return 0;

	return (int)(sheet->getRetanguloFrame(anim_atual, frame_atual)->larg*escala.x);
}

int Sprite::getAltura()
{
	if (!sheet)
		return 0;

	return (int)(sheet->getRetanguloFrame(anim_atual, frame_atual)->alt*escala.y);
}

int	Sprite::getLarguraOriginal()
{
	if (!sheet)
		return 0;

	return sheet->getRetanguloFrame(anim_atual, frame_atual)->larg;
}

int Sprite::getAlturaOriginal()
{
	if (!sheet)
		return 0;

	return sheet->getRetanguloFrame(anim_atual, frame_atual)->alt;
}

int Sprite::getAnimacao()
{
	return anim_atual;
}

int Sprite::getFrame()
{
	return frame_atual;
}

float Sprite::getVelocidadeAnimacao()
{
	return vel_anim;
}

bool Sprite::getPause()
{
	return (flags & FLAG_SPRITE_ANIM_PAUSADA) != 0;
}

bool Sprite::getInverterX()
{
	Uint8 flip = flags & FLAG_SPRITE_INV_XY;
	return (flip & FLAG_SPRITE_INV_X) != 0;
}

bool Sprite::getInverterY()
{
	Uint8 flip = flags & FLAG_SPRITE_INV_XY;
	return (flip & FLAG_SPRITE_INV_Y) != 0;
}

Cor Sprite::getCor()
{
	return cor;
}

int Sprite::getCorVermelho()
{
	return cor.r;
}

int Sprite::getCorVerde()
{
	return cor.g;
}

int Sprite::getCorAzul()
{
	return cor.b;
}

int Sprite::getCorAlpha()
{
	return cor.a;
}

bool Sprite::estaTocandoAnimacaoAoContrario()
{
	return (flags & FLAG_SPRITE_ANIM_AO_CONTRARIO) != 0;
}

SpriteSheet *Sprite::getSpriteSheet()
{
	return sheet;
}

void Sprite::obterAncora(float &ax, float &ay)
{
	ax = ancora.x;
	ay = ancora.y;
}

void Sprite::obterEscala(float &ex, float& ey)
{
	ex = escala.x;
	ey = escala.y;
}

void Sprite::obterTamanho(int &larg, int &alt)
{
	if (sheet)
	{
		Quad* f = sheet->getRetanguloFrame(anim_atual, frame_atual);
		larg = (int)(f->larg*escala.x);
		alt = (int)(f->alt*escala.y);
	}
	else
	{
		larg = alt = 0;
	}
}

void Sprite::obterTamanhoOriginal(int &larg, int &alt)
{
	if (sheet)
	{
		Quad* f = sheet->getRetanguloFrame(anim_atual, frame_atual);
		larg = f->larg;
		alt = f->alt;
	}
	else
	{
		larg = alt = 0;
	}
}

void Sprite::obterCor(int &r, int &g, int &b)
{
	r = cor.r;
	g = cor.g;
	b = cor.b;
}

void Sprite::obterCor(int &r, int &g, int &b, int &a)
{
	r = cor.r;
	g = cor.g;
	b = cor.b;
	a = cor.a;
}

bool Sprite::terminouAnimacao()
{
	return (flags & FLAG_SPRITE_ANIM_TERMINOU) != 0;
}

void Sprite::setAncora(Vetor2D anc)
{
	ancora = anc;
}

void Sprite::setAncora(float x, float y)
{
	ancora.x = x;
	ancora.y = y;
}

void Sprite::setEscala(Vetor2D esc)
{
	escala = esc;
}

void Sprite::setEscala(float ex, float ey)
{
	escala.x = ex;
	escala.y = ey;
}

void Sprite::setAnimacao(int anim, bool recomecar)
{
	if(recomecar)
	{
		anim_atual = anim;	//	set anim_atual antes de recomecar
		recomecarAnimacao();
	}
	else if(sheet)
		if(sheet->getNumFramesDaAnimacao(anim) < sheet->getNumFramesDaAnimacao(anim_atual))
		{
			frame_atual = frame_atual%(sheet->getNumFramesDaAnimacao(anim));
		}

	anim_atual = anim;
}

void Sprite::setFrame(int frame)
{
	frame_atual = frame;
}

void Sprite::setVelocidadeAnimacao(float vel)
{
	vel_anim = vel;
}

void Sprite::setPause(bool p)
{
	if (p)
		flags = flags | FLAG_SPRITE_ANIM_PAUSADA;
	else
		flags = flags & ~FLAG_SPRITE_ANIM_PAUSADA;
}

void Sprite::setInverterX(bool b)
{
	if (b)
		flags = flags | FLAG_SPRITE_INV_X;
	else
		flags = flags & ~FLAG_SPRITE_INV_X;
}

void Sprite::setInverterY(bool b)
{
	if (b)
		flags = flags | FLAG_SPRITE_INV_Y;
	else
		flags = flags & ~FLAG_SPRITE_INV_Y;
}

void Sprite::setCor(Cor cor)
{
	this->cor = cor;
}

void Sprite::setCor(int r, int g, int b)
{
	cor.r = r;
	cor.g = g;
	cor.b = b;
}

void Sprite::setCor(int r, int g, int b, int a)
{
	cor.r = r;
	cor.g = g;
	cor.b = b;
	cor.a = a;
}

void Sprite::setCorVermelho(int vermelho)
{
	cor.r = vermelho;
}

void Sprite::setCorVerde(int verde)
{
	cor.g = verde;
}

void Sprite::setCorAzul(int azul)
{
	cor.b = azul;
}

void Sprite::setCorAlpha(int alpha)
{
	cor.a = alpha;
}

void Sprite::setAnimacaoAoContrario(bool b)
{
	if (b)
		flags = flags | FLAG_SPRITE_ANIM_AO_CONTRARIO;
	else
		flags = flags & ~FLAG_SPRITE_ANIM_AO_CONTRARIO;
}

void Sprite::setSpriteSheet(string nome)
{
	setSpriteSheet(gRecursos.getSpriteSheet(nome));
}

void Sprite::setSpriteSheet(SpriteSheet *sheet)
{
	if(!sheet)
		return;

	this->sheet = sheet;

	anim_atual = 0;
	frame_atual = 0;
}

void Sprite::recomecarAnimacao()
{
	if(flags & FLAG_SPRITE_ANIM_AO_CONTRARIO)
	{
		frame_atual = sheet->getNumFramesDaAnimacao(anim_atual)-1;
		tempo_anim = sheet->getNumFramesDaAnimacao(anim_atual)/vel_anim;
	}
	else
	{
		frame_atual = 0;
		tempo_anim = 0;
	}

	flags = flags & ~FLAG_SPRITE_ANIM_TERMINOU;
}

void Sprite::avancarAnimacao()
{
	avancarAnimacao(gTempo.getDeltaTempo());
}

void Sprite::avancarAnimacao(float dt)
{
	if(flags & FLAG_SPRITE_ANIM_PAUSADA)
		return;

	if(vel_anim == 0.0f)
		return;

	float max_frames = (float)sheet->getNumFramesDaAnimacao(anim_atual);

	if(flags & FLAG_SPRITE_ANIM_AO_CONTRARIO)
	{
		tempo_anim -= dt;
		if (tempo_anim <= 0.0f && !terminouAnimacao())
			flags |= FLAG_SPRITE_ANIM_TERMINOU;
		else
			flags &= ~FLAG_SPRITE_ANIM_TERMINOU;

		while(tempo_anim < 0)
			tempo_anim += max_frames/vel_anim;		
	}
	else
	{
		tempo_anim += dt;
		if(tempo_anim >= max_frames/vel_anim && !terminouAnimacao())
			flags |= FLAG_SPRITE_ANIM_TERMINOU;
		else
			flags &= ~FLAG_SPRITE_ANIM_TERMINOU;

		while(tempo_anim > max_frames/vel_anim)
			tempo_anim -= max_frames/vel_anim;
	}

	frame_atual = (int)(tempo_anim*vel_anim);
}

bool Sprite::desenhar(int x, int y, float rot)
{
	//if(!uniEstaInicializada()) 
		//return false;

	if(!sheet)
	{
		gDebug.erro("Nao pode desenhar Sprite antes de setar SpriteSheet", this);
		return false;
	}

	Quad* f = sheet->getRetanguloFrame(anim_atual, frame_atual);
	int inverter = flags & FLAG_SPRITE_INV_XY;
	return gGraficos.desenharTextura(sheet->getTextura(), *f, x, y, rot, ancora.x, ancora.y, escala.x, escala.y, cor, (EnumInverterDesenho)inverter);
}
