#ifndef UNI_ESTADO_H
#define UNI_ESTADO_H

#include "uniAPI.h"
#include "MaquinaDeEstados.h"
#include "MaquinaDeEstadosComPilha.h"

class UNI_API Estado
{
public:
	Estado();
	~Estado();

	virtual void entrar(){};
	virtual void sair(){};
	virtual void atualizar(float dt) {};

	void atualizar();

	MaquinaDeEstados* getMaquinaDeEstados();
	MaquinaDeEstadosComPilha* getMaquinaDeEstadosComPilha();
	void setMaquinaDeEstados(MaquinaDeEstados* maquina);

protected:
	MaquinaDeEstados *maquinaDeEstados;
};

#endif