#include "uniEase.h"
#include <math.h>

#ifndef PI
	#define PI 3.14159265358979
#endif

using namespace std;

//	linear
float uniEaseLinear(float t, float d, float i, float desloc)
{
	return (desloc * t / d) + i;
}

float uniEaseInLinear(float t, float d, float i, float desloc)
{
	return uniEaseLinear(t, d, i, desloc);
}

float uniEaseOutLinear(float t, float d, float i, float desloc)
{
	return uniEaseLinear(t, d, i, desloc);
}

float uniEaseInOutLinear(float t, float d, float i, float desloc)
{
	return uniEaseLinear(t, d, i, desloc);
}

//	seno
float uniEaseInSin(float t, float d, float i, float desloc)
{
	return -desloc * cos(t / d * (PI / 2.0f)) + desloc + i;
}

float uniEaseOutSin(float t, float d, float i, float desloc)
{
	return desloc * sin(t / d * (PI / 2.0f)) + i;
}

float uniEaseInOutSin(float t, float d, float i, float desloc)
{
	return -desloc / 2.0f * (cos(PI*t / d) - 1) + i;
}

//	quadrático
float uniEaseInQuad(float t, float d, float i, float desloc)
{
	return desloc * (t /= d)*t + i;
}

float uniEaseOutQuad(float t, float d, float i, float desloc)
{
	return -desloc * (t /= d)*(t - 2.0f) + i;
}

float uniEaseInOutQuad(float t, float d, float i, float desloc)
{
	if ((t /= d / 2.0f) < 1)
		return desloc / 2.0f * t*t + i;

	return -desloc / 2.0f * ((--t)*(t - 2.0f) - 1) + i;
}

//	cúbico
float uniEaseInCub(float t, float d, float i, float desloc)
{
	return desloc*(t /= d)*t*t + i;
}

float uniEaseOutCub(float t, float d, float i, float desloc)
{
	return desloc*((t = t / d - 1)*t*t + 1) + i;
}

float uniEaseInOutCub(float t, float d, float i, float desloc)
{
	if ((t /= d / 2.0f) < 1)
		return desloc / 2.0f * t*t*t + i;

	return desloc / 2.0f * ((t -= 2.0f)*t*t + 2.0f) + i;
}

//	quártico
float uniEaseInQuart(float t, float d, float i, float desloc)
{
	return desloc * (t /= d)*t*t*t + i;
}

float uniEaseOutQuart(float t, float d, float i, float desloc)
{
	return -desloc * ((t = t / d - 1)*t*t*t - 1) + i;
}

float uniEaseInOutQuart(float t, float d, float i, float desloc)
{
	if ((t /= d / 2.0f) < 1)
		return desloc / 2.0f * t*t*t*t + i;

	return -desloc / 2.0f * ((t -= 2.0f)*t*t*t - 2.0f) + i;
}

//	quíntico
float uniEaseInQuint(float t, float d, float i, float desloc)
{
	return desloc*(t /= d)*t*t*t*t + i;
}

float uniEaseOutQuint(float t, float d, float i, float desloc)
{
	return desloc*((t = t / d - 1)*t*t*t*t + 1) + i;
}

float uniEaseInOutQuint(float t, float d, float i, float desloc)
{
	if ((t /= d / 2.0f) < 1)
		return desloc / 2.0f * t*t*t*t*t + i;

	return desloc / 2.0f * ((t -= 2.0f)*t*t*t*t + 2.0f) + i;
}

//	exponencial base 2
float uniEaseInExpo(float t, float d, float i, float desloc)
{
	return (t == 0) ? i : desloc * pow(2, 10 * (t / d - 1)) + i;
}

float uniEaseOutExpo(float t, float d, float i, float desloc)
{
	return (t == d) ? i + desloc : desloc * (-pow(2, -10 * t / d) + 1) + i;
}

float uniEaseInOutExpo(float t, float d, float i, float desloc)
{
	if (t == 0) 
		return i;

	if (t == d) 
		return i + desloc;

	if ((t /= d / 2.0f) < 1)
		return desloc / 2.0f * pow(2, 10 * (t - 1)) + i;

	return desloc / 2.0f * (-pow(2, -10 * --t) + 2) + i;
}

//	circular
float uniEaseInCirc(float t, float d, float i, float desloc)
{
	return -desloc * (sqrt(1 - (t /= d)*t) - 1) + i;
}

float uniEaseOutCirc(float t, float d, float i, float desloc)
{
	return desloc * sqrt(1 - (t = t / d - 1)*t) + i;
}

float uniEaseInOutCirc(float t, float d, float i, float desloc)
{
	if ((t /= d / 2.0f) < 1)
		return -desloc / 2.0f * (sqrt(1 - t*t) - 1) + i;

	return desloc / 2.0f * (sqrt(1 - (t -= 2)*t) + 1) + i;
}

//	cúbico excedido 
float uniEaseInBack(float t, float d, float i, float desloc)
{
	float s = 1.70158f;
	return desloc*(t /= d)*t*((s + 1)*t - s) + i;
}

float uniEaseOutBack(float t, float d, float i, float desloc)
{
	float s = 1.70158f;
	return desloc*((t = t / d - 1)*t*((s + 1)*t + s) + 1) + i;
}

float uniEaseInOutBack(float t, float d, float i, float desloc)
{
	float s = 1.70158f;
	if ((t /= d / 2.0f) < 1) 
		return desloc / 2.0f * (t*t*(((s *= (1.525f)) + 1)*t - s)) + i;

	return desloc / 2.0f * ((t -= 2.0f)*t*(((s *= (1.525f)) + 1)*t + s) + 2.0f) + i;
}

//	seno exponencial amortecida
float uniEaseInElastic(float t, float d, float i, float desloc)
{
	float s = 1.70158f; 
	float p = 0.0f;
	float a = desloc;

	if (t == 0) 
		return i;  
	if ((t /= d) == 1) 
		return i + desloc;  
	if (!p) 
		p = d*.3;

	if (a < fabsf(desloc)) 
	{ 
		a = desloc; 
		s = p / 4.0f;
	}
	else
	{
		s = p / (2.0f * PI) * asin(desloc / a);
	}

	return -(a*pow(2, 10 * (t -= 1)) * sin((t*d - s)*(2.0f * PI) / p)) + i;
}

float uniEaseOutElastic(float t, float d, float i, float desloc)
{
	float s = 1.70158f;
	float p = 0.0f;
	float a = desloc;

	if (t == 0) 
		return i;  
	if ((t /= d) == 1) 
		return i + desloc;  
	if (!p) 
		p = d*.3;

	if (a < fabsf(desloc))
	{ 
		a = desloc; 
		s = p / 4.0f;
	}
	else
	{
		s = p / (2.0f * PI) * asin(desloc / a);
	}

	return a*pow(2, -10 * t) * sin((t*d - s)*(2.0f * PI) / p) + desloc + i;
}

float uniEaseInOutElastic(float t, float d, float i, float desloc)
{
	float s = 1.70158f;
	float p = 0.0f;
	float a = desloc;

	if (t == 0) 
		return i; 
	if ((t /= d / 2.0f) == 2.0f)
		return i + desloc;  
	if (!p) p = d*(.3*1.5);

	if (a < fabsf(desloc))
	{ 
		a = desloc; 
		s = p / 4.0f;
	}
	else
	{
		s = p / (2.0f * PI) * asin(desloc / a);
	}

	if (t < 1) 
		return -.5*(a*pow(2, 10 * (t -= 1)) * sin((t*d - s)*(2.0f * PI) / p)) + i;

	return a*pow(2, -10 * (t -= 1)) * sin((t*d - s)*(2.0f * PI) / p)*.5 + desloc + i;
}

//	 exponencial decadente
float uniEaseInBounce(float t, float d, float i, float desloc)
{
	return desloc - uniEaseOutBounce(d - t, d, 0, desloc) + i;
}

float uniEaseOutBounce(float t, float d, float i, float desloc)
{
	if ((t /= d) < (1.0f / 2.75f)) 
		return desloc*(7.5625f*t*t) + i;
	else if (t < (2.0f / 2.75f))
		return desloc*(7.5625f*(t -= (1.5 / 2.75))*t + .75) + i;
	else if (t < (2.5f / 2.75f))
		return desloc*(7.5625f*(t -= (2.25 / 2.75))*t + .9375) + i;
	else 
		return desloc*(7.5625f*(t -= (2.625 / 2.75))*t + .984375) + i;
}

float uniEaseInOutBounce(float t, float d, float i, float desloc)
{
	if (t < d / 2.0f)
		return uniEaseInBounce(t * 2.0f, d, 0, desloc) * .5 + i;

	return uniEaseOutBounce(t * 2.0f - d, d, 0, desloc) * .5 + desloc*.5 + i;
}
