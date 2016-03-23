#include "uniRand.h"

void uniRandSetSemente(unsigned int semente)
{
	srand(semente);
}

int	uniRandEntre(int min, int max)
{
	return min + rand() % (1 + max - min);
}

char uniRandEntre(char min, char max)
{
	return min + rand() % (1 + max - min);
}

float uniRandEntre(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

double uniRandEntre(double min, double max)
{
	return min + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (max - min)));
}

unsigned int uniRandEntre(unsigned int min, unsigned int max)
{
	return min + rand() % (1 + max - min);
}

Vetor2D uniRandEntre(const Vetor2D& min, const Vetor2D& max)
{
	return Vetor2D(uniRandEntre(min.x, max.x), uniRandEntre(min.y, max.y));
}

//
int	uniRandEntreZeroEUmInt()
{
	return uniRandEntre(0, 99) / 50;
}

float uniRandEntreZeroEUmFloat()
{
	return uniRandEntre(0.0f, 1.0f);
}

double uniRandEntreZeroEUmDouble()
{
	return uniRandEntre(0.0, 1.0);
}

Vetor2D uniRandEntreZeroEUmVetor2D()
{
	return uniRandEntre(Vetor2D(0.0f, 0.0f), Vetor2D(1.0f, 1.0f));
}

int	uniRandEntreMenosUmEUmInt()
{
	return (uniRandEntre(0, 99) - 50) / 33;
}

float uniRandEntreMenosUmEUmFloat()
{
	return uniRandEntre(-1.0f, 1.0f);
}

double uniRandEntreMenosUmEUmDouble()
{
	return uniRandEntre(-1.0, 1.0);
}

Vetor2D uniRandEntreMenosUmEUmVetor2D()
{
	return uniRandEntre(Vetor2D(-1.0f, -1.0f), Vetor2D(1.0f, 1.0f));
}