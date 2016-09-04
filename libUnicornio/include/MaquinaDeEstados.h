#ifndef UNI_MAQUINADEESTADOS_H
#define UNI_MAQUINADEESTADOS_H

#include "uniAPI.h"

class Estado;

class UNI_API MaquinaDeEstados
{
public:
	MaquinaDeEstados();
	virtual ~MaquinaDeEstados();

	//	Métodos virtuais
	virtual bool inicializar(Estado* estado);
	virtual bool finalizar();
	virtual void aoInicializar();
	virtual void aoFinalizar();

	virtual void atualizar(float dt);

	virtual void trocarEstado(Estado* proxEstado);

	//	Métodos normais
	void atualizar();
	bool estaInicializada();

protected:
	Estado* proxEstado;
	Estado* estadoAtual;
	bool trocandoEstado;
	bool inicializada;
};

#endif