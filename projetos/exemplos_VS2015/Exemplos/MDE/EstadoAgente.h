#pragma once

#include "libUnicornio.h"
#include "Agente.h"

//	Classe base para todos os estados da classe Agente
//		Essa classe não faz a implementação de nenhum
//		método da classe pai. Simplesmente possui um
//		método para pegar um ponteiro para o agente que
//		deve ser a própria maquina de estados, ou seja,
//		a classe Agente deve ser filha da classe MaquinaDeEstados
//
//		Também possui um método para pegar o Sprite do agente,
//		só por facilidade.
class EstadoAgente: public Estado
{
public:
	EstadoAgente();
	virtual ~EstadoAgente();

	Agente* getAgente();
	Sprite* getSprite();
};

