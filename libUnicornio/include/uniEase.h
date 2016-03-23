#ifndef UNI_UNIEASE_H
#define UNI_UNIEASE_H

//	linear
float uniEaseLinear(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseInLinear(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseOutLinear(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseInOutLinear(float tempo, float duracao, float inicio, float deslocamento);

//	seno
float uniEaseInSin(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseOutSin(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseInOutSin(float tempo, float duracao, float inicio, float deslocamento);

//	quadrático
float uniEaseInQuad(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseOutQuad(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseInOutQuad(float tempo, float duracao, float inicio, float deslocamento);

//	cúbico
float uniEaseInCub(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseOutCub(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseInOutCub(float tempo, float duracao, float inicio, float deslocamento);

//	quártico
float uniEaseInQuart(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseOutQuart(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseInOutQuart(float tempo, float duracao, float inicio, float deslocamento);

//	quíntico
float uniEaseInQuint(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseOutQuint(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseInOutQuint(float tempo, float duracao, float inicio, float deslocamento);

//	exponencial base 2
float uniEaseInExpo(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseOutExpo(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseInOutExpo(float tempo, float duracao, float inicio, float deslocamento);

//	circular
float uniEaseInCirc(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseOutCirc(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseInOutCirc(float tempo, float duracao, float inicio, float deslocamento);

//	cúbico excedido 
float uniEaseInBack(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseOutBack(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseInOutBack(float tempo, float duracao, float inicio, float deslocamento);

//	seno exponencial amortecida
float uniEaseInElastic(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseOutElastic(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseInOutElastic(float tempo, float duracao, float inicio, float deslocamento);

//	 exponencial decadente
float uniEaseInBounce(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseOutBounce(float tempo, float duracao, float inicio, float deslocamento);
float uniEaseInOutBounce(float tempo, float duracao, float inicio, float deslocamento);

#endif
