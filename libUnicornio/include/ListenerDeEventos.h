#ifndef UNI_LISTENERDEEVENTOS_H
#define UNI_LISTENERDEEVENTOS_H

#include "SDL_events.h"

class ListenerDeEventos
{
public:
	ListenerDeEventos();
	virtual ~ListenerDeEventos();

	virtual bool processarEvento(const SDL_Event& evento) = 0;
};

#endif