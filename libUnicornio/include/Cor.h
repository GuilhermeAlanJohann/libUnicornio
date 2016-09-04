#ifndef UNI_COR_H
#define UNI_COR_H

#include "uniAPI.h"
#include "SDL_Pixels.h"

class UNI_API Cor :public SDL_Color
{
public:
	Cor();
	Cor(Uint8 _r, Uint8 _g, Uint8 _b);
	Cor(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a);
	Cor(const Cor& c);
	Cor(const SDL_Color& c);
	~Cor();

	Cor& operator=(const Cor& c);
	Cor& operator=(const SDL_Color& c);
	bool operator == (const Cor& c);
	bool operator == (const SDL_Color& c);
	bool operator != (const Cor& c);
	bool operator != (const SDL_Color& c);

	SDL_Color getSDL_Color();
	void set(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	Uint32 getARGB();
	Uint32 getRGBA();
};

#endif