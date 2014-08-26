#include "Vetor2D.h"
#include <math.h>
#include <float.h>

Vetor2D::Vetor2D()
{
}

Vetor2D::Vetor2D(float x, float y):
	x(x),
	y(y) 
{}

Vetor2D::~Vetor2D()
{
}

Vetor2D Vetor2D::operator-() const 
{ 
	Vetor2D v; 
	v.set(-x, -y); 
	return v; 
}
	
float Vetor2D::operator()(int i) const
{
	return (&x)[i];
}

float& Vetor2D::operator()(int i)
{
	return (&x)[i];
}

bool Vetor2D::operator==(const Vetor2D& v)
{
	return (abs(x-v.x) < FLT_EPSILON && abs(y - v.y) < FLT_EPSILON);
}

bool Vetor2D::operator!=(const Vetor2D& v)
{
	return !(*this == v);
}

void Vetor2D::operator+=(const Vetor2D& v)
{
	x += v.x; y += v.y;
}
	
void Vetor2D::operator-=(const Vetor2D& v)
{
	x -= v.x; y -= v.y;
}

void Vetor2D::operator*=(float a)
{
	x *= a; y *= a;
}

void Vetor2D::operator/=(float a)
{
	x /= a; y /= a;
}

Vetor2D Vetor2D::operator+(const Vetor2D& v)
{
	return Vetor2D(x + v.x, y + v.y);
}

Vetor2D Vetor2D::operator-(const Vetor2D& v)
{
	return Vetor2D(x - v.x, y - v.y);
}

void Vetor2D::set(float x_, float y_) 
{ 
	x = x_; 
	y = y_; 
}

void Vetor2D::zerar()
{ 
	x = 0.0f;
	y = 0.0f; 
}

float Vetor2D::comprimento() const
{
	return sqrt(x * x + y * y);
}

float Vetor2D::comprimentoAoQuadrado() const
{
	return x * x + y * y;
}

float Vetor2D::normalizar()
{
	float compr = comprimento();
	if (compr < FLT_EPSILON)
	{
		return 0.0f;
	}
	float invCompr = 1.0f / compr;
	x *= invCompr;
	y *= invCompr;

	return compr;
}