#include "Arma.h"


Arma::Arma()
{
	numBalas = 0;
}

Arma::~Arma()
{
}

void Arma::setAudio(string nome)
{
	//	2)	setar audio no som
	som.setAudio(nome);

	//	(OPCIONAL) setar volume (0 - 100)
	som.setVolume(50);
}

void Arma::recarregar(int num)
{
	numBalas = num;
}

void Arma::atirar()
{
	if(numBalas > 0)
	{
		//	3)	tocar
		som.tocar();

		numBalas--;
	}
}

int Arma::getNumBalas()
{
	return numBalas;
}