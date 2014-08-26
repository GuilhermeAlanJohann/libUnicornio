#include "Sprite.h"
#include "libUnicornio.h"

Sprite::Sprite()
	:sheet(NULL), frame_atual(0), anim_atual(0), tempo_anim(0), vel_anim(2.0), ancora_x(0.5), ancora_y(0.5), flip_mode(SDL_FLIP_NONE), animacao_ao_contrario(false), pause(false)
{
	clip.x = 0;
	clip.y = 0;
	clip.w = 0;
	clip.h = 0;
	escala_x = 1.0;
	escala_y = 1.0;
	cor.r = 255;
	cor.g = 255;
	cor.b = 255;
	cor.a = 255;
	terminou_anim = false;
}

Sprite::Sprite(const Sprite& cp)
{
	sheet = cp.sheet;
	frame_atual = 0;
	anim_atual = 0;
	tempo_anim = cp.tempo_anim;
	vel_anim = cp.vel_anim;
	ancora_x = cp.ancora_x;
	ancora_y = cp.ancora_y;
	flip_mode = cp.flip_mode;
	animacao_ao_contrario = cp.animacao_ao_contrario;
	escala_x = cp.escala_x;
	escala_y = cp.escala_y;
	clip = cp.clip;
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
		ancora_x = r.ancora_x;
		ancora_y = r.ancora_y;
		flip_mode = r.flip_mode;
		animacao_ao_contrario = r.animacao_ao_contrario;
		escala_x = r.escala_x;
		escala_y = r.escala_y;
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
		&& ancora_x == r.ancora_x 
		&& ancora_y == r.ancora_y 
		&& flip_mode == r.flip_mode 
		&& escala_x == r.escala_x 
		&& escala_y == r.escala_y 
		&& clip.x == r.clip.x 
		&& clip.y == r.clip.y 
		&& clip.w == r.clip.w 
		&& clip.h == r.clip.h 
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

float Sprite::getAncoraX()
{
	return ancora_x;
}

float Sprite::getAncoraY()
{
	return ancora_y;
}

float Sprite::getEscalaX()
{
	return escala_x;
}

float Sprite::getEscalaY()
{
	return escala_y;
}

int	Sprite::getLargura()
{
	return clip.w*escala_x;
}

int Sprite::getAltura()
{
	return clip.h*escala_y;
}

int	Sprite::getLarguraOriginal()
{
	return clip.w;
}

int Sprite::getAlturaOriginal()
{
	return clip.h;
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

SpriteSheet* Sprite::getSpriteSheet()
{
	return sheet;
}

void Sprite::obterAncora(float &x, float &y)
{
	x = ancora_x;
	y = ancora_y;
}

void Sprite::obterEscala(float &sx, float& sy)
{
	sx = escala_x;
	sy = escala_y;
}

void Sprite::obterTamanho(int &w, int &h)
{
	w = clip.w*escala_x;
	h = clip.h*escala_y;
}

void Sprite::obterTamanhoOriginal(int &w, int &h)
{
	w = clip.w;
	h = clip.h;
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
	if(!sheet)
	{
		return false;
	}

	return terminou_anim;
}

void Sprite::setAncora(float x, float y)
{
	ancora_x = x;
	ancora_y = y;
}

void Sprite::setEscala(float sx, float sy)
{
	escala_x = sx;
	escala_y = sy;
}

void Sprite::setAnimacao(int anim, bool recomecar)
{
	anim_atual = anim;

	if(recomecar)
	{
		recomecarAnimacao();
	}
	else if(sheet->getNumFramesAnimacao(anim) < sheet->getNumFramesAnimacao(anim_atual))
	{
		frame_atual = frame_atual%(sheet->getNumFramesAnimacao(anim));
		clip.x = frame_atual*clip.w;
		clip.y = anim_atual*clip.h;
	}
}

void Sprite::setFrame(int frame)
{
	frame_atual = frame;
	clip.x = frame_atual*clip.w;
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

void Sprite::setSpriteSheet(SpriteSheet* sheet)
{
	if(!sheet)
	{
		return;
	}

	if(sheet == this->sheet)
	{
		return;
	}

	this->sheet = sheet;

	clip.x = 0;
	clip.y = 0;
	sheet->obterTamanhoCelula(clip.w, clip.h);

	anim_atual = 0;
	frame_atual = 0;
}

void Sprite::recomecarAnimacao()
{
	if(animacao_ao_contrario)
	{
		frame_atual = sheet->getNumFramesAnimacao(anim_atual)-1;
		tempo_anim = sheet->getNumFramesAnimacao(anim_atual)/vel_anim;
	}
	else
	{
		frame_atual = 0;
		tempo_anim = 0;
	}

	terminou_anim = false;

	clip.x = frame_atual*clip.w;
	clip.y = anim_atual*clip.h;
}

void Sprite::avancarAnimacao()
{
	avancarAnimacao(deltaTempo);
}

void Sprite::avancarAnimacao(float dt)
{
	if(pause)
	{
		return;
	}

	if(vel_anim == 0)
	{
		return;
	}

	float max_frames = sheet->getNumFramesAnimacao(anim_atual);

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

	frame_atual = tempo_anim*vel_anim;

	clip.x = frame_atual*clip.w;
	clip.y = anim_atual*clip.h;
}

bool Sprite::desenhar(int x, int y, float rot)
{
	if(!uni_init) return false;

	if(!sheet)
	{
		uniDesenharTexto("Nao pode desenhar Sprite antes de setar sprite_sheet.",x,y,255,0,0);
		return false;
	}

	SDL_Rect rect;
	rect.w = clip.w*escala_x;
	rect.h = clip.h*escala_y;

    SDL_Point pivot = {rect.w * ancora_x, rect.h * ancora_y};

	rect.x = x - pivot.x;
	rect.y = y - pivot.y;

	// seta cor
	SDL_SetTextureColorMod(sheet->getTextura(), cor.r, cor.g, cor.b);
	SDL_SetTextureAlphaMod(sheet->getTextura(), cor.a);

    //	Draw the texture
	SDL_RenderCopyEx(renderer, sheet->getTextura(), &clip, &rect, rot, &pivot, flip_mode);

	return true;
}
