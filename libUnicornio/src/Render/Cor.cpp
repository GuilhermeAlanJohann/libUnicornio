#include "Cor.h"

Cor::Cor() 
{ 
	r = g = b = 0; 
	a = 255; 
};

Cor::Cor(Uint8 _r, Uint8 _g, Uint8 _b) 
{ 
	r = _r; 
	g = _g; 
	b = _b; 
	a = 255; 
};

Cor::Cor(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a) 
{ 
	r = _r; 
	g = _g; 
	b = _b; 
	a = _a; 
};

Cor::Cor(const Cor& c)
{
	if (*this != c)
	{
		*this = c;
	}
};

Cor::Cor(const SDL_Color& c)
{
	if (*this != c)
	{
		*this = c;
	}
};

Cor::~Cor()
{};

Cor& Cor::operator=(const Cor& c)
{
	a = c.a;
	r = c.r;
	g = c.g;
	b = c.b;
	return *this;
}

Cor& Cor::operator=(const SDL_Color& c)
{
	a = c.a;
	r = c.r;
	g = c.g;
	b = c.b;
	return *this;
}

bool Cor::operator == (const Cor& c)
{
	return (a == c.a && r == c.r && g == c.g && b == c.b);
}

bool Cor::operator == (const SDL_Color& c)
{
	return (a == c.a && r == c.r && g == c.g && b == c.b);
}

bool Cor::operator != (const Cor& c)
{
	return !(*this == c);
}

bool Cor::operator != (const SDL_Color& c)
{
	return !(*this == c);
}

SDL_Color Cor::getSDL_Color()
{
	SDL_Color c;
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return c;
}

void Cor::set(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Uint32 Cor::getARGB()
{
	return (a << 24) | (r << 16) | (g << 8) | b;
}

Uint32 Cor::getRGBA()
{
	return (r << 24) | (g << 16) | (b << 8) | a;
}