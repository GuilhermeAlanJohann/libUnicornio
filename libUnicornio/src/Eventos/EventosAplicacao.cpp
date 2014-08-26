#include "Eventos.h"

EventosAplicacao::EventosAplicacao()
{
	sair = false;
}

EventosAplicacao::~EventosAplicacao()
{}

void EventosAplicacao::atualizar()
{
	iOS.atualizar();
}

void EventosAplicacao::processarEvento(const SDL_Event& evento)
{
	switch(evento.type)
	{
	case SDL_QUIT:
		sair = true;
		break;

	default:
		iOS.processarEvento(evento);
	}
}