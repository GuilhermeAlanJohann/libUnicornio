#include "Estado.h"
#include "Global.h"
#include "MaquinaDeEstadosComPilha.h"

Estado::Estado()
{
}

Estado::~Estado()
{
}

void Estado::atualizar()
{
	atualizar(gTempo.getDeltaTempo());
}

MaquinaDeEstados* Estado::getMaquinaDeEstados()
{
	return maquinaDeEstados;
}

MaquinaDeEstadosComPilha* Estado::getMaquinaDeEstadosComPilha()
{
	return (MaquinaDeEstadosComPilha*)maquinaDeEstados;
}

void Estado::setMaquinaDeEstados(MaquinaDeEstados* maquina)
{
	maquinaDeEstados = maquina;
}