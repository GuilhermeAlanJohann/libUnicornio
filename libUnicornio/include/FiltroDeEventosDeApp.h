#ifndef UNI_FILTRODEEVENTOSDEAPP_H
#define UNI_FILTRODEEVENTOSDEAPP_H

class FiltroDeEventosDeApp
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