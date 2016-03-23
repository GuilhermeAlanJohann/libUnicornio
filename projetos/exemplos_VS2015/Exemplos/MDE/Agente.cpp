#include "Agente.h"
#include "EstadoParado.h"


Agente::Agente()
{
}

Agente::~Agente()
{
}

void Agente::inicializar()
{
	//	Ajusta a ancora para ficar mais ou menos em cima da cabeça do personagem
	spr.setAncora(0.25, 0.5);	

	pos.set(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	rot = 0;

	//	1.1) Chama o método de inicialização da classe pai (MaquinaDeEstados).
	//			É aqui que a maquina de estados é inicializada realmente.
	//			Fazemos isso passando o estado inicial como parâmetro.
	MaquinaDeEstados::inicializar(new EstadoParado);
}

bool Agente::finalizar()
{
	//	Chama o método de finalização da classe pai
	return MaquinaDeEstados::finalizar();
}

void Agente::atualizar()
{
	//	Chama o método de atualização da classe pai
	MaquinaDeEstados::atualizar();
}

void Agente::desenhar()
{
	spr.desenhar(pos.x, pos.y, rot);
}

Sprite* Agente::getSprite()
{
	return &spr;
}

Vetor2D Agente::getPos()
{
	return pos;
}

float Agente::getRot()
{
	return rot;
}

void Agente::setPos(Vetor2D p)
{
	pos = p;
}

void Agente::setRot(float r)
{
	rot = r;
}

