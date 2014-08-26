#include "Eventos.h"
#include "libUnicornio.h"
 
Eventos::Eventos()
{
	aplicacao = NULL;
	mouse = NULL;
	teclado = NULL;
	joysticks = NULL;
	toques = NULL;
}

Eventos::~Eventos()
{
}

void Eventos::atualizar()
{
	aplicacao->atualizar();
	mouse->atualizar();
	teclado->atualizar();
	joysticks->atualizar();
	toques->atualizar();
	

	SDL_PumpEvents();

	SDL_Event evento;
	while(SDL_PollEvent(&evento))
	{
		aplicacao->processarEvento(evento);
		mouse->processarEvento(evento);
		teclado->processarEvento(evento);
		joysticks->processarEvento(evento);
		toques->processarEvento(evento);
	}
}