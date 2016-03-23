#pragma once

#include "EstadoAgente.h"
#include "EstadoGirando.h"

//	Classe que representa o estado "parado" do agente.
//		Filha da classe EstadoAgente.
//		Implementa os m�todos virtuais da classe Estado.
class EstadoParado: public EstadoAgente
{
public:
	EstadoParado();
	~EstadoParado();

	//	Reimplementa��o de m�todos virtuais da classe pai (Estado)
	void entrar();
	void sair();
	void atualizar(float dt);
};

