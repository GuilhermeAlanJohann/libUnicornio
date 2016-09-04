#ifndef UNI_NODOASTAR_H
#define UNI_NODOASTAR_H

#include "uniAPI.h"
#include "Vetor2D.h"

struct UNI_API NodoAStar
{
public:
	NodoAStar();
	~NodoAStar();

	bool operator==(const NodoAStar& n);
	bool operator!=(const NodoAStar& n);

	NodoAStar* anterior;

	Vetor2D pos;
	Vetor2D posRelativa;

	int custoF;
	int custoG;
	int custoH;
	int custoAdicional;

	bool caminhavel;

	bool estaNaListaAberta;
	bool estaNaListaFechada;
};

#endif
