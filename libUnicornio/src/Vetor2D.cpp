#include "Vetor2D.h"
#include <math.h>
#include <float.h>
#include <stdlib.h>

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
	return (fabsf(x-v.x) < FLT_EPSILON && fabsf(y - v.y) < FLT_EPSILON);
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

void Vetor2D::operator*=(const Vetor2D& v)
{
	x *= v.x; y *= v.y;
}
	
void Vetor2D::operator/=(const Vetor2D& v)
{
	x /= v.x; y /= v.y;
}

void Vetor2D::operator+=(float a)
{
	x += a; y += a;
}

void Vetor2D::operator-=(float a)
{
	x -= a; y -= a;
}

void Vetor2D::operator*=(float a)
{
	x *= a; y *= a;
}

void Vetor2D::operator/=(float a)
{
	x /= a; y /= a;
}

void Vetor2D::operator+=(double a)
{
	*this += (float)a;
}

void Vetor2D::operator-=(double a)
{
	*this -= (float)a;
}

void Vetor2D::operator*=(double a)
{
	*this *= (float)a;
}

void Vetor2D::operator/=(double a)
{
	*this /= (float)a;
}

void Vetor2D::operator+=(int a)
{
	*this += (float)a;
}

void Vetor2D::operator-=(int a)
{
	*this -= (float)a;
}

void Vetor2D::operator*=(int a)
{
	*this *= (float)a;
}

void Vetor2D::operator/=(int a)
{
	*this /= (float)a;
}

Vetor2D Vetor2D::operator+(const Vetor2D& v)
{
	return Vetor2D(x + v.x, y + v.y);
}

Vetor2D Vetor2D::operator-(const Vetor2D& v)
{
	return Vetor2D(x - v.x, y - v.y);
}

Vetor2D Vetor2D::operator*(const Vetor2D& v)
{
	return Vetor2D(x * v.x, y * v.y);
}

Vetor2D Vetor2D::operator/(const Vetor2D& v)
{
	return Vetor2D(x / v.x, y / v.y);
}

Vetor2D Vetor2D::operator+(float a)
{
	return Vetor2D(x + a, y + a);
}

Vetor2D Vetor2D::operator-(float a)
{
	return Vetor2D(x - a, y - a);
}

Vetor2D Vetor2D::operator*(float a)
{
	return Vetor2D(x * a, y * a);
}

Vetor2D Vetor2D::operator/(float a)
{
	return Vetor2D(x / a, y / a);
}

Vetor2D Vetor2D::operator+(double a)
{
	return (*this + (float)a);
}

Vetor2D Vetor2D::operator-(double a)
{
	return (*this - (float)a);
}

Vetor2D Vetor2D::operator*(double a)
{
	return (*this * (float)a);
}

Vetor2D Vetor2D::operator/(double a)
{
	return (*this / (float)a);
}

Vetor2D Vetor2D::operator+(int a)
{
	return (*this + (float)a);
}

Vetor2D Vetor2D::operator-(int a)
{
	return (*this - (float)a);
}

Vetor2D Vetor2D::operator*(int a)
{
	return (*this * (float)a);
}

Vetor2D Vetor2D::operator/(int a)
{
	return (*this / (float)a);
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
	return sqrtf(x * x + y * y);
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

void Vetor2D::rotacionar(float angulo)
{
	float rad = angulo*PI / 180;
	float cs = cosf(rad);
	float sn = sinf(rad);
	float xx = x*cs - y*sn;
	float yy = x*sn + y*cs;
	x = xx;
	y = yy;
}

float Vetor2D::getAnguloAteVetor(const Vetor2D& vet)
{
	float r = atan2f(vet.y, vet.x) - atan2f(y, x);
	r *= 180 / PI;
	if (r < -180.0f)
		r += 360.0f;
	if (r > 180.0f)
		r -= 360.0f;
	return r;
}

float Vetor2D::getAnguloAPartirDoVetor(const Vetor2D& vet)
{
	float r = atan2f(y, x) - atan2f(vet.y, vet.x);
	r *= 180 / PI;
	if (r < -180.0f)
		r += 360.0f;
	if (r > 180.0f)
		r -= 360.0f;
	return r;
}

float Vetor2D::getAngulo()
{
	return getAnguloAPartirDoVetor(Vetor2D(1, 0));
}

Vetor2D Vetor2D::getNormal()
{
	float invCompr = 1.0f / comprimento();
	return Vetor2D(x * invCompr, y * invCompr);
}

Vetor2D Vetor2D::getRotacionado(float angulo)
{
	float rad = angulo*PI / 180;
	float cs = cosf(rad);
	float sn = sinf(rad);
	return Vetor2D(x*cs - y*sn, x*sn + y*cs);
}