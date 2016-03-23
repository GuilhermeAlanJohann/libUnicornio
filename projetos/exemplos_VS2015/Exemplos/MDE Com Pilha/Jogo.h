#pragma once
#include "libUnicornio.h"
#include "TelaInicial.h"

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();

private:
	MaquinaDeEstadosComPilha maquina;
};

