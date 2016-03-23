#ifndef UNI_UNIRAND_H
#define UNI_UNIRAND_H

#include <math.h>
#include <random>
#include "Vetor2D.h"

void uniRandSetSemente(unsigned int semente);

int		uniRandEntre(int min, int max);
char	uniRandEntre(char min, char max);
float	uniRandEntre(float min, float max);
double	uniRandEntre(double min, double max);
unsigned int uniRandEntre(unsigned int min, unsigned int max);
Vetor2D uniRandEntre(const Vetor2D& min, const Vetor2D& max);

int		uniRandEntreZeroEUmInt();
float	uniRandEntreZeroEUmFloat();
double	uniRandEntreZeroEUmDouble();
Vetor2D uniRandEntreZeroEUmVetor2D();

int		uniRandEntreMenosUmEUmInt();
float	uniRandEntreMenosUmEUmFloat();
double	uniRandEntreMenosUmEUmDouble();
Vetor2D uniRandEntreMenosUmEUmVetor2D();

#endif
