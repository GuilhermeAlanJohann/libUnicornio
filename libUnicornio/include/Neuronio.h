#ifndef UNI_NEURONIO_H
#define UNI_NEURONIO_H

#include <vector>
#include "uniRand.h"

using namespace std;

class ConexaoNeural
{
public:
	double peso;
	double deltaPeso;
};

class Neuronio
{
public:
	Neuronio();
	Neuronio(int num_saidas);
	Neuronio(const vector<double>& pesos);
	~Neuronio();

	vector<ConexaoNeural> conexoes; //	conexoes de saida
	double valorDeSaida;
	double delta;

private:

};

#endif

