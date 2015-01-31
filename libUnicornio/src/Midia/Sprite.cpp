#include "Sprite.h"
#include "libUnicornio.h"

Sprite::Sprite()
	:sheet(NULL), frame_atual(0), anim_atual(0), tempo_anim(0.0), vel_anim(2.0f), flip_mode(SDL_FLIP_NONE), animacao_ao_contrario(false), pause(false)
{
	ancora.set(0.5f, 0.5f);
	escala.set(1.0f, 1.0f);
	cor.r = 255;
	cor.g = 255;
	cor.b = 255;
	cor.a = 255;
	terminou_anim = false;
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
	flip_mode = cp.flip_mode;
	animacao_ao_contrario = cp.animacao_ao_contrario;
	pause = cp.pause;
	cor = cp.cor;
	terminou_anim = cp.terminou_anim;
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
		flip_mode = r.flip_mode;
		animacao_ao_contrario = r.animacao_ao_contrario;
		pause = r.pause;
		cor = r.cor;
		terminou_anim = r.terminou_anim;
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
		&& flip_mode == r.flip_mode 
		&& animacao_ao_contrario == r.animacao_ao_contrario 
		&& pause == r.pause 
		&& cor.r == r.cor.r 
		&& cor.g == r.cor.g 
		&& cor.b == r.cor.b 
		&& cor.a == r.cor.a 
		&& terminou_anim == r.terminou_anim);
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
	return (int)(sheet->getFrame(anim_atual, frame_atual)->larg*escala.x);
}

int Sprite::getAltura()
{
	return (int)(sheet->getFrame(anim_atual, frame_atual)->alt*escala.y);
}

int	Sprite::getLarguraOriginal()
{
	return sheet->getFrame(anim_atual, frame_atual)->larg;
}

int Sprite::getAlturaOriginal()
{
	return sheet->getFrame(anim_atual, frame_atual)->alt;
}

int Sprite::getAnimacaoAtual()
{
	return anim_atual;
}

int Sprite::getFrameAtual()
{
	return frame_atual;
}

bool Sprite::getPause()
{
	return pause;
}

bool Sprite::getInverterX()
{
	return (bool)(flip_mode & SDL_FLIP_HORIZONTAL);
}

bool Sprite::getInverterY()
{
	return (bool)(flip_mode & SDL_FLIP_VERTICAL);
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
	Frame *f = sheet->getFrame(anim_atual, frame_atual);
	larg = (int)(f->larg*escala.x);
	alt = (int)(f->alt*escala.y);
}

void Sprite::obterTamanhoOriginal(int &larg, int &alt)
{
	Frame *f = sheet->getFrame(anim_atual, frame_atual);
	larg = f->larg;
	alt = f->alt;
}

void Sprite::obterCor(int &vermelho, int &verde, int &azul)
{
	vermelho = cor.r;
	verde = cor.g;
	azul = cor.b;
}

void Sprite::obterCor(int &vermelho, int &verde, int &azul, int &alpha)
{
	vermelho = cor.r;
	verde = cor.g;
	azul = cor.b;
	alpha = cor.a;
}

bool Sprite::terminouAnimacao()
{
	return terminou_anim;
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
	else if(sheet->getNumFramesDaAnimacao(anim) < sheet->getNumFramesDaAnimacao(anim_atual))
	{
		frame_atual = frame_atual%(sheet->getNumFramesDaAnimacao(anim));
	}

	anim_atual = anim;
}

void Sprite::setFrame(int frame)
{
	frame_atual = frame;
}

void Sprite::setPause(bool p)
{
	pause = p;
}

void Sprite::setVelocidadeAnimacao(float vel)
{
	vel_anim = vel;
}

void Sprite::setInverterX(bool b)
{
	if(b)
	{
		flip_mode = (SDL_RendererFlip)(flip_mode | SDL_FLIP_HORIZONTAL);
	}
	else
	{
		if((flip_mode & SDL_FLIP_VERTICAL) == SDL_FLIP_VERTICAL)
		{
			flip_mode = SDL_FLIP_VERTICAL;
		}
		else
		{
			flip_mode = SDL_FLIP_NONE;
		}
	}
}

void Sprite::setInverterY(bool b)
{
	if(b)
	{
		flip_mode = (SDL_RendererFlip)(flip_mode | SDL_FLIP_VERTICAL);
	}
	else
	{
		if((flip_mode & SDL_FLIP_HORIZONTAL) == SDL_FLIP_HORIZONTAL)
		{
			flip_mode = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			flip_mode = SDL_FLIP_NONE;
		}
	}
}

void Sprite::setCor(int vermelho, int verde, int azul, int alpha)
{
	cor.r = vermelho;
	cor.g = verde;
	cor.b = azul;
	cor.a = alpha;
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
	animacao_ao_contrario = b;
}

void Sprite::setSpriteSheet(string nome)
{
	setSpriteSheet(recursos.getSpriteSheet(nome));
}

void Sprite::setSpriteSheet(SpriteSheet *sheet)
{
	if(!sheet)
	{
		return;
	}

	this->sheet = sheet;

	anim_atual = 0;
	frame_atual = 0;
}

void Sprite::recomecarAnimacao()
{
	if(animacao_ao_contrario)
	{
		frame_atual = sheet->getNumFramesDaAnimacao(anim_atual)-1;
		tempo_anim = sheet->getNumFramesDaAnimacao(anim_atual)/vel_anim;
	}
	else
	{
		frame_atual = 0;
		tempo_anim = 0;
	}

	terminou_anim = false;
}

void Sprite::avancarAnimacao()
{
	avancarAnimacao(deltaTempo);
}

void Sprite::avancarAnimacao(double dt)
{
	if(pause)
	{
		return;
	}

	if(vel_anim == 0)
	{
		return;
	}

	float max_frames = (float)sheet->getNumFramesDaAnimacao(anim_atual);

	if(animacao_ao_contrario)
	{
		tempo_anim -= dt;
		if(tempo_anim <= 0.0f && !terminou_anim)
			terminou_anim = true;
		else
			terminou_anim = false;

		while(tempo_anim < 0)
		{
			tempo_anim += max_frames/vel_anim;
		}
	}
	else
	{
		tempo_anim += dt;
		if(tempo_anim >= max_frames/vel_anim && !terminou_anim)
			terminou_anim = true;
		else
			terminou_anim = false;

		while(tempo_anim > max_frames/vel_anim)
		{
			tempo_anim -= max_frames/vel_anim;
		}
	}

	frame_atual = (int)(tempo_anim*vel_anim);
}

bool Sprite::desenhar(int x, int y, float rot)
{
	if(!uni_init) return false;

	if(!sheet)
	{
		uniDesenharTexto("Nao pode desenhar Sprite antes de setar SpriteSheet.", x, y, 255, 0, 0);
		return false;
	}

	Frame *f = sheet->getFrame(anim_atual, frame_atual);

	SDL_Rect clip;
	clip.x = f->x0;
	clip.y = f->y0;
	clip.w = f->larg;
	clip.h = f->alt;

	SDL_Rect rect;
	rect.w = (int)(clip.w*escala.x);
	rect.h = (int)(clip.h*escala.y);

    SDL_Point pivot = {(int)(rect.w * ancora.x), (int)(rect.h * ancora.y)};

	rect.x = x - pivot.x;
	rect.y = y - pivot.y;

	// seta cor
	SDL_SetTextureColorMod(sheet->getSDL_Texture(), cor.r, cor.g, cor.b);
	SDL_SetTextureAlphaMod(sheet->getSDL_Texture(), cor.a);

    //	Draw the texture
	SDL_RenderCopyEx(renderer, sheet->getSDL_Texture(), &clip, &rect, rot, &pivot, flip_mode);

	return true;
}
