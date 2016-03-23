#ifndef UNI_RETANGULO_H
#define UNI_RETANGULO_H

#include "SDL_rect.h"

struct Retangulo
{
	Retangulo() :x(0), y(0), largura(0), altura(0)
	{}

	Retangulo(Sint16 _x, Sint16 _y, Sint16 larg, Sint16 alt) :x(_x), y(_y), largura(larg), altura(alt)
	{}

	bool operator==(const Retangulo& r) const
	{
		return (x == r.x && y == r.y && largura == r.largura && altura == r.altura);
	}

	bool operator!=(const Retangulo& r) const
	{
		return !(*this == r);
	}

	SDL_Rect getSDL_Rect() const
	{
		SDL_Rect retan;
		retan.x = x;
		retan.y = y;
		retan.w = largura;
		retan.h = altura;
		return retan;
	}

	Sint16 x;
	Sint16 y;
	Sint16 largura;
	Sint16 altura;
};

#endif
