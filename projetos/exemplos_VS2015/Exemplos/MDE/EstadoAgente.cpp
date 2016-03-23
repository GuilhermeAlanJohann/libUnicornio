#include "EstadoAgente.h"



EstadoAgente::EstadoAgente()
{
}

EstadoAgente::~EstadoAgente()
{
}

Agente* EstadoAgente::getAgente()
{
	//	O agente � a pr�pria maquina de estados.
	//	Uma expecializa��o dela.
	//	Ent�o retorna a maquina fazendo o cast para Agente*
	return (Agente*)getMaquinaDeEstados();
}

Sprite* EstadoAgente::getSprite()
{
	//	Retorna o sprite do agente
	return getAgente()->getSprite();
}