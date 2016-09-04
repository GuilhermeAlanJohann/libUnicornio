#include "Quad.h"


Quad::Quad() 
{};

Quad::Quad(int _x, int _y, int _larg, int _alt)
		:x(_x), y(_y), larg(_larg), alt(_alt)
{};

Quad::Quad(const Quad& q)
{
	if (*this != q)
		*this = q;
}

Quad::~Quad() 
{};

Quad& Quad::operator=(const Quad& q)
{
	x = q.x;
	y = q.y;
	larg = q.larg;
	alt = q.alt;
	return *this;
}

Quad& Quad::operator=(const SDL_Rect& r)
{
	x = r.x;
	y = r.y;
	larg = r.w;
	alt = r.h;
	return *this;
}

bool Quad::operator==(const Quad& q)
{
	return (x == q.x && y == q.y && larg == q.larg && alt == q.alt);
}

bool Quad::operator==(const Quad& q) const
{
	return (x == q.x && y == q.y && larg == q.larg && alt == q.alt);
}

bool Quad::operator!=(const Quad& q)
{
	return !(*this == q);
}

bool Quad::operator!=(const Quad& q) const
{
	return !(*this == q);
}

bool Quad::operator==(const SDL_Rect& r)
{
	return (x == r.x && y == r.y && larg == r.w && alt == r.h);
}

bool Quad::operator==(const SDL_Rect& r) const
{
	return (x == r.x && y == r.y && larg == r.w && alt == r.h);
}

bool Quad::operator!=(const SDL_Rect& r)
{
	return !(*this == r);
}

bool Quad::operator!=(const SDL_Rect& r) const
{
	return !(*this == r);
}

void Quad::set(int x, int y, int larg, int alt)
{
	this->x = x;
	this->y = y;
	this->larg = larg;
	this->alt = alt;
}

void Quad::zerar()
{
	x = y = larg = alt = 0;
}

SDL_Rect Quad::getSDL_Rect()
{
	return{ (int)x, (int)y, (int)larg, (int)alt };
}

SDL_Rect Quad::getSDL_Rect() const
{
	return{ (int)x, (int)y, (int)larg, (int)alt };
}