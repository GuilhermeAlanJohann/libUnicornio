#include "Eventos.h"

EventosAplicacao::EventosAplicacao()
{
	sair = false;

	appEstaTerminando = false;
	appTemPoucaMemoria = false;
	appVaiEntrarEmPlanoDeFundo = false;
	appEntrouEmPlanoDeFundo = false;
	appVaiEntrarEmPrimeiroPlano = false;
	appEntrouEmPrimeiroPlano = false;
}

EventosAplicacao::~EventosAplicacao()
{}

void EventosAplicacao::atualizar()
{
	appEstaTerminando = false;
	appTemPoucaMemoria = false;		// isso aqui pode gerar um problema. (nao ha como saber se ja liberou memoria)
	appVaiEntrarEmPlanoDeFundo = false;
	appEntrouEmPlanoDeFundo = false;
	appVaiEntrarEmPrimeiroPlano = false;
	appEntrouEmPrimeiroPlano = false;
}

void EventosAplicacao::processarEvento(const SDL_Event& evento)
{
	switch(evento.type)
	{
	case SDL_QUIT:
		sair = true;
		break;

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