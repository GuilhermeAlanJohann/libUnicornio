#pragma once

#include "libUnicornio.h"
#include "Agente.h"

//	Classe base para todos os estados da classe Agente
//		Essa classe n�o faz a implementa��o de nenhum
//		m�todo da classe pai. Simplesmente possui um
//		m�todo para pegar um ponteiro para o agente que
//		deve ser a pr�pria maquina de estados, ou seja,
//		a classe Agente deve ser filha da classe MaquinaDeEstados
//
//		Tamb�m possui um m�todo para pegar o Sprite do agente,
//		s� por facilidade.
class EstadoAgente: public Estado
{
public:
	EstadoAgente();
	virtual ~EstadoAgente();

	Agente* getAgente();
	Sprite* getSprite();
};

