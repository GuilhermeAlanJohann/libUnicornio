#include "Eventos.h"
#include "SDL.h"

EventosTeclado::EventosTeclado()
{
	pressionou = new Uint8[NUMERO_DE_TECLAS];
	segurando = new Uint8[NUMERO_DE_TECLAS];
	soltou = new Uint8[NUMERO_DE_TECLAS];

	for(int i = 0; i < NUMERO_DE_TECLAS; ++i)
	{
		pressionou[i] = false;
		segurando[i] = false;
		soltou[i] = false;
	}
}

EventosTeclado::~EventosTeclado()
{
	delete[] pressionou;
	delete[] segurando;
	delete[] soltou; 
}

void EventosTeclado::atualizar()
{
	for(int i = 0; i < NUMERO_DE_TECLAS; ++i)
	{
		pressionou[i] = false;
		soltou[i] = false;
	}
}

void EventosTeclado::processarEvento(const SDL_Event& evento)
{
	switch(evento.type)
	{
	case SDL_KEYDOWN:
		{
			Uint8 scancode = evento.key.keysym.scancode;

			if(evento.key.state == SDL_PRESSED && !segurando[scancode])
			{
				pressionou[scancode] = true;
			}

			segurando[scancode] = true;
		}
		break;

	case SDL_KEYUP:
		{
			Uint8 scancode = evento.key.keysym.scancode;
			segurando[scancode] = false;

			if(evento.key.state == SDL_RELEASED)
			{
				soltou[scancode] = true;
			}
		}
		break;
	}
}