#ifndef UNI_MAQUINADEESTADOSCOMPILHA_H
#define UNI_MAQUINADEESTADOSCOMPILHA_H

#include <stack>
#include "MaquinaDeEstados.h"

using namespace std;

class MaquinaDeEstadosComPilha: public MaquinaDeEstados
{
public:
	MaquinaDeEstadosComPilha();
	virtual ~MaquinaDeEstadosComPilha();

	//	M�todos virtuais
	bool inicializar(Estado* estado);
	bool finalizar();
	void atualizar(float dt);
	void trocarEstado(Estado* proxEstado);

	//void aoInicializar(){};
	//void aoFinalizar(){};

	//	M�todos normais
	void atualizar();
	void empilharEstado(Estado* estado);
	void desempilharEstado();

	bool temEstados();

private:
	stack<Estado*> pilhaDeEstados;

	bool empilhandoEstado;
	bool desempilhandoEstado;
};

#endif