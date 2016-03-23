#include "Neuronio.h"

Neuronio::Neuronio()
{
}

Neuronio::Neuronio(int num_saidas)
{
	conexoes.resize(num_saidas);
	for (unsigned int i = 0; i < num_saidas; ++i)
	{
		conexoes[i].peso = uniRandEntre(-1.0f, 1.0f);
	}
}

Neuronio::Neuronio(const vector<double>& pesos)
{
	conexoes.resize(pesos.size());
	for (unsigned int i = 0; i < pesos.size(); ++i)
	{
		conexoes[i].peso = pesos[i];
	}
}

Neuronio::~Neuronio()
{
}