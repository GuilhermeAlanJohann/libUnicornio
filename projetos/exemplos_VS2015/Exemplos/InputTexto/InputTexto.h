#pragma once

#include "libUnicornio.h"

class InputTexto
{
public:
	InputTexto();
	~InputTexto();

	void inicializar();
	void finalizar();

	void atualizar();
	void desenhar();

private:
	Texto txt;
};

