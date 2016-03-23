#pragma once

#include "Comida.h"
#include "Agente.h"

#define NUM_COMIDAS 30
#define NUM_AGENTES 3

class Ambiente
{
public:
	Ambiente();
	~Ambiente();

	void inicializar();
	void finalizar();

	void atualizar();
	void desenhar();

	void atualizarColisoes();

	void sortearPosComida(int indice);

	Comida& getComida(int indice);

	bool comidaColidiuComAlgumAgente(int indice);


private:
	vector<Comida> comidas;
	vector<Agente> agentes;
};

