#pragma once
#include "EstadoAgente.h"

//	Classe que representa o estado "girando" do agente.
//		Filha da classe EstadoAgente.
//		Implementa os m�todos virtuais da classe Estado.
class EstadoGirando :public EstadoAgente
{
public:
	EstadoGirando(Vetor2D p);
	~EstadoGirando();

	//	Reimplementa��o de m�todos virtuais da classe pai (Estado)
	void entrar();
	void sair();
	void atualizar(float dt);

private:
	Vetor2D destino;
};

