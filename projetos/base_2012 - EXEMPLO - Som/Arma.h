#pragma once
#include "libUnicornio.h"


class Arma
{
public:
	Arma();
	~Arma();

	void setAudio(string nome);
	void recarregar(int num);

	void atirar();
	int getNumBalas();

private:
	Som som;
	int numBalas;
};

