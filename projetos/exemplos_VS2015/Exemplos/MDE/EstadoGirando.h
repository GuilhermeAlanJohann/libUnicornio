#pragma once
#include "EstadoAgente.h"

//	Classe que representa o estado "girando" do agente.
//		Filha da classe EstadoAgente.
//		Implementa os métodos virtuais da classe Estado.
class EstadoGirando :public EstadoAgente
{
public:
	EstadoGirando(Vetor2D p);
	~EstadoGirando();

	//	Reimplementação de métodos virtuais da classe pai (Estado)
	void entrar();
	void sair();
	void atualizar(float dt);

private:
	Vetor2D destino;
};

