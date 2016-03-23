#include "EstadoAgente.h"



EstadoAgente::EstadoAgente()
{
}

EstadoAgente::~EstadoAgente()
{
}

Agente* EstadoAgente::getAgente()
{
	//	O agente é a própria maquina de estados.
	//	Uma expecialização dela.
	//	Então retorna a maquina fazendo o cast para Agente*
	return (Agente*)getMaquinaDeEstados();
}

Sprite* EstadoAgente::getSprite()
{
	//	Retorna o sprite do agente
	return getAgente()->getSprite();
}