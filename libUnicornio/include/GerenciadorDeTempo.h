#ifndef UNI_GERENCIADORDETEMPO_H
#define UNI_GERENCIADORDETEMPO_H

#include "uniAPI.h"
#include "SDL_timer.h"

class UNI_API GerenciadorDeTempo
{
public:
	GerenciadorDeTempo();
	~GerenciadorDeTempo();

	void inicializar();
	void finalizar();

	void atualizar(bool limitarFPS);

	Uint64 getTicks();
	double getTempoEntreTicks(Uint64 ticksInicio, Uint64 ticksFim);
	double getTempoAteTickAtual(Uint64 ticksAnterior);

	double getFPS();
	Uint32 getLimiteFPS();
	Uint64 getDeltaTempoEmMicrosegundos();
	double getDeltaTempoEmMilisegundos();
	double getDeltaTempo();

	void setLimiteFPS(Uint32 limiteFPS);

private:
	Uint32 limiteFPS;		//	frames por segundo (válido somente quando paramento limitarFPS = true no metodo atualizar)
	Uint64 deltaTempoUs;	//	tempo em microsegundos

	Uint64 tickAntes;		//	tempo em ticks
	Uint64 tickAtual;		//	tempo em ticks
};

#endif