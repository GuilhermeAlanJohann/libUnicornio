#ifndef UNI_UNIEASE_H
#define UNI_UNIEASE_H

#include "uniAPI.h"

//	linear
float UNI_API uniEaseLinear(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseInLinear(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseOutLinear(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseInOutLinear(float tempo, float duracao, float inicio, float deslocamento);

//	seno
float UNI_API uniEaseInSin(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseOutSin(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseInOutSin(float tempo, float duracao, float inicio, float deslocamento);

//	quadrático
float UNI_API uniEaseInQuad(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseOutQuad(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseInOutQuad(float tempo, float duracao, float inicio, float deslocamento);

//	cúbico
float UNI_API uniEaseInCub(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseOutCub(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseInOutCub(float tempo, float duracao, float inicio, float deslocamento);

//	quártico
float UNI_API uniEaseInQuart(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseOutQuart(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseInOutQuart(float tempo, float duracao, float inicio, float deslocamento);

//	quíntico
float UNI_API uniEaseInQuint(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseOutQuint(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseInOutQuint(float tempo, float duracao, float inicio, float deslocamento);

//	exponencial base 2
float UNI_API uniEaseInExpo(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseOutExpo(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseInOutExpo(float tempo, float duracao, float inicio, float deslocamento);

//	circular
float UNI_API uniEaseInCirc(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseOutCirc(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseInOutCirc(float tempo, float duracao, float inicio, float deslocamento);

//	cúbico excedido 
float UNI_API uniEaseInBack(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseOutBack(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseInOutBack(float tempo, float duracao, float inicio, float deslocamento);

//	seno exponencial amortecida
float UNI_API uniEaseInElastic(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseOutElastic(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseInOutElastic(float tempo, float duracao, float inicio, float deslocamento);

//	 exponencial decadente
float UNI_API uniEaseInBounce(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseOutBounce(float tempo, float duracao, float inicio, float deslocamento);
float UNI_API uniEaseInOutBounce(float tempo, float duracao, float inicio, float deslocamento);

#endif
