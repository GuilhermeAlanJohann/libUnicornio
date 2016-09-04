#ifndef UNI_FILTRODEEVENTOSDEAPP_H
#define UNI_FILTRODEEVENTOSDEAPP_H

#include "uniAPI.h"

class UNI_API FiltroDeEventosDeApp
{
public:
	FiltroDeEventosDeApp();
	virtual ~FiltroDeEventosDeApp();

	virtual void quandoAppEstaTerminando();
	virtual void quandoAppEstaComPoucaMemoria();
	virtual void quandoAppVaiEntrarEmPlanoDeFundo();
	virtual void quandoAppEntrouEmPlanoDeFundo();
	virtual void quandoAppVaiEntrarEmPrimeiroPlano();
	virtual void quandoAppEntrouEmPrimeiroPlano();

};

#endif