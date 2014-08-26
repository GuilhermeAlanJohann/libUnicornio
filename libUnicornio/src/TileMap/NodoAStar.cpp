#include "NodoAStar.h"


NodoAStar::NodoAStar()
{
	anterior = 0;

	pos.zerar();
	posRelativa.zerar();

	custoF = 0;
	custoG = 0;
	custoH = 0;
	custoAdicional = 0;

	caminhavel = true;

	estaNaListaAberta = false;
	estaNaListaFechada = false;
}

NodoAStar::~NodoAStar()
{
}

bool NodoAStar::operator==(const NodoAStar& n)
{
	return (pos == n.pos);
}

bool NodoAStar::operator!=(const NodoAStar& n)
{
	return !(*this == n);
}