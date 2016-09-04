#include "Fading.h"
#include "Global.h"

Fading::Fading()
{
	cor = Cor(0, 0, 0, 255);

	tempo = 0.0f;
	duracao = 1.0f;

	executandoFadeIn = false;
	executandoFadeOut = false;
	_terminouFadeIn = false;
	_terminouFadeOut = false;
}

Fading::~Fading()
{
}

void Fading::atualizar()
{
	atualizar(gTempo.getDeltaTempo());
}

void Fading::atualizar(double dt)
{
	if (estaExecutandoFadeIn())
	{
		tempo -= dt;
		if (tempo <= 0)
		{
			tempo = 0;
			_terminouFadeIn = true;
			executandoFadeIn = false;
		}
	}
	else if(estaExecutandoFadeOut())
	{
		tempo += dt;
		if (tempo >= duracao)
		{
			tempo = duracao;
			_terminouFadeOut = true;
			executandoFadeOut = false;
		}
	}
}

void Fading::desenhar()
{
	int alpha = (tempo / duracao)*cor.a;

	if (alpha == 0)
		return;

	/*SDL_Texture* tex = gGraficos.getSDL_TextureBranco();
	SDL_SetTextureColorMod(tex, cor.r, cor.g, cor.b);
	SDL_SetTextureAlphaMod(tex, alpha);
	SDL_Rect dest = { 0, 0, gJanela.getLargura(), gJanela.getAltura() };
	SDL_RenderCopy(gGraficos.sdl_renderer, tex, NULL, &dest);*/
	Quad r(0, 0, gJanela.getLargura(), gJanela.getAltura());
	gGraficos.desenharRetangulo(r, cor.r, cor.g, cor.b, alpha, true);
}

void Fading::cancelar()
{
	executandoFadeIn = false;
	executandoFadeOut = false;
	_terminouFadeIn = false;
	_terminouFadeOut = false;
	tempo = 0;
}

void Fading::iniciarFadeIn()
{
	executandoFadeIn = true;
	executandoFadeOut = false;
	_terminouFadeIn = false;
	_terminouFadeOut = false;
	//if(tempo <= 0.0f)
		tempo = duracao;
}

void Fading::iniciarFadeOut()
{
	executandoFadeIn = false;
	executandoFadeOut = true;
	_terminouFadeIn = false;
	_terminouFadeOut = false;
	//if (tempo >= duracao)
		tempo = 0.0f;
}

void Fading::terminarFadeIn()
{
	executandoFadeIn = false;
	_terminouFadeIn = true;
	tempo = 0.0f;
}

void Fading::terminarFadeOut()
{
	executandoFadeOut = false;
	_terminouFadeOut = true;
	tempo = duracao;
}

bool Fading::estaExecutando()
{
	return executandoFadeIn || executandoFadeOut;
}

bool Fading::estaExecutandoFadeIn()
{
	return executandoFadeIn;
}

bool Fading::estaExecutandoFadeOut()
{
	return executandoFadeOut;
}

bool Fading::terminou()
{
	return _terminouFadeIn || _terminouFadeOut;
}

bool Fading::terminouFadeIn()
{
	return _terminouFadeIn;
}

bool Fading::terminouFadeOut()
{
	return _terminouFadeOut;
}

void Fading::setTerminouFadeIn(bool b)
{
	_terminouFadeIn = b;
}

void Fading::setTerminouFadeOut(bool b)
{
	_terminouFadeOut = b;
}

Cor Fading::getCor()
{
	return cor;
}

Cor Fading::getCorAtual()
{
	Cor r(cor.r, cor.g, cor.b, (tempo / duracao)*cor.a);
	return r;
}

void Fading::obterCor(Uint8& r, Uint8& g, Uint8& b, Uint8& a)
{
	r = cor.r;
	g = cor.g;
	b = cor.b;
	a = cor.a;
}

void Fading::obterCorAtual(Uint8& r, Uint8& g, Uint8& b, Uint8& a)
{
	r = cor.r;
	g = cor.g;
	b = cor.b;
	a = (tempo / duracao)*cor.a;
}

void Fading::setCor(Cor c)
{
	cor = c;
}

void Fading::setCor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	cor.set(r, g, b, a);
}

double Fading::getDuracao()
{
	return duracao;
}

void Fading::setDuracao(double t)
{
	duracao = t;
}