#ifndef UNI_LISTENERDEEVENTOS_H
#define UNI_LISTENERDEEVENTOS_H

#include "uniAPI.h"
#include "SDL_events.h"

class UNI_API ListenerDeEventos
{
public:
	ListenerDeEventos();
	virtual ~ListenerDeEventos();

	virtual bool processarEvento(const SDL_Event& evento) = 0;
};

#endif