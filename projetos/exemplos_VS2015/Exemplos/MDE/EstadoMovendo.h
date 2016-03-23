#pragma once
#include "EstadoAgente.h"

//	Classe que representa o estado "movendo" do agente.
//		Filha da classe EstadoAgente.
//		Implementa os métodos virtuais da classe Estado.
class EstadoMovendo :public EstadoAgente
{
public:
	EstadoMovendo(Vetor2D p);
	~EstadoMovendo();

	//	Reimplementação de métodos virtuais da classe pai (Estado)
	void entrar();
	void sair();
	void atualizar(float dt);

private:
	Vetor2D destino;
};

