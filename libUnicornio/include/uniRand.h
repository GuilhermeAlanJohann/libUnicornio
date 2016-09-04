#ifndef UNI_UNIRAND_H
#define UNI_UNIRAND_H

#include "uniAPI.h"
#include <math.h>
#include <random>
#include "Vetor2D.h"

void UNI_API uniRandSetSemente(unsigned int semente);

int		UNI_API uniRandEntre(int min, int max);
char	UNI_API uniRandEntre(char min, char max);
float	UNI_API uniRandEntre(float min, float max);
double	UNI_API uniRandEntre(double min, double max);
unsigned int UNI_API uniRandEntre(unsigned int min, unsigned int max);
Vetor2D UNI_API uniRandEntre(const Vetor2D& min, const Vetor2D& max);

int		UNI_API uniRandEntreZeroEUmInt();
float	UNI_API uniRandEntreZeroEUmFloat();
double	UNI_API uniRandEntreZeroEUmDouble();
Vetor2D UNI_API uniRandEntreZeroEUmVetor2D();

int		UNI_API uniRandEntreMenosUmEUmInt();
float	UNI_API uniRandEntreMenosUmEUmFloat();
double	UNI_API uniRandEntreMenosUmEUmDouble();
Vetor2D UNI_API uniRandEntreMenosUmEUmVetor2D();

#endif
