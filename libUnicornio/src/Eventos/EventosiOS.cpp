#include "Eventos.h"

EventosiOS::EventosiOS()
{
	appEstaTerminando = false;
	appTemPoucaMemoria = false;
	appVaiEntrarEmPlanoDeFundo = false;
	appEntrouEmPlanoDeFundo = false;
	appVaiEntrarEmPrimeiroPlano = false;
	appEntrouEmPrimeiroPlano = false;
}

EventosiOS::~EventosiOS()
{}

void EventosiOS::atualizar()
{
	appEstaTerminando = false;
	appTemPoucaMemoria = false;		// isso aqui gera um problema.
	appVaiEntrarEmPlanoDeFundo = false;
	appEntrouEmPlanoDeFundo = false;
	appVaiEntrarEmPrimeiroPlano = false;
	appEntrouEmPrimeiroPlano = false;
}

void EventosiOS::processarEvento(const SDL_Event& evento)
{
	switch(evento.type)
	{
	case SDL_APP_TERMINATING:
		appEstaTerminando = true;
		break;

	case SDL_APP_LOWMEMORY:
		appTemPoucaMemoria = true;
		break;

	case SDL_APP_WILLENTERBACKGROUND:
		appVaiEntrarEmPlanoDeFundo = true;
		break;

	case SDL_APP_DIDENTERBACKGROUND:
		appEntrouEmPlanoDeFundo = true;
		break;

	case SDL_APP_WILLENTERFOREGROUND:
		appVaiEntrarEmPrimeiroPlano = true;
		break;

	case SDL_APP_DIDENTERFOREGROUND:
		appEntrouEmPrimeiroPlano = true;
		break;
	}
}