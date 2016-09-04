#ifndef UNI_QUAD_H
#define UNI_QUAD_H

#include "uniAPI.h"
#include "SDL_rect.h"

class UNI_API Quad
{
public:
	Quad();
	Quad(int _x, int _y, int _larg, int _alt);
	Quad(const Quad& q);
	~Quad();

	Quad& operator=(const Quad& q);
	Quad& operator=(const SDL_Rect& r);

	bool operator==(const Quad& q);
	bool operator==(const Quad& q) const;
	bool operator!=(const Quad& q);
	bool operator!=(const Quad& q) const;

	bool operator==(const SDL_Rect& r);
	bool operator==(const SDL_Rect& r) const;
	bool operator!=(const SDL_Rect& r);
	bool operator!=(const SDL_Rect& r) const;

	void set(int x, int y, int larg, int alt);
	void zerar();

	SDL_Rect getSDL_Rect();
	SDL_Rect getSDL_Rect() const;

	Sint16 x, y;
	Sint16 larg, alt;
};

#endif
