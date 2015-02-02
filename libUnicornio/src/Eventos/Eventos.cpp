#include "Eventos.h"
#include "libUnicornio.h"
 
Eventos::Eventos()
{
	aplicacao = NULL;
	mouse = NULL;
	teclado = NULL;
	joysticks = NULL;
	telaDeToque = NULL;

	usandoFila = false;
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
	telaDeToque->atualizar();
	
	SDL_PumpEvents();
	limparFila();

	SDL_Event evento;
	while(SDL_PollEvent(&evento))
	{
		aplicacao->processarEvento(evento);
		mouse->processarEvento(evento);
		teclado->processarEvento(evento);
		joysticks->processarEvento(evento);
		telaDeToque->processarEvento(evento);

		if(usandoFila)
			fila_eventos.push(evento);
	}
}

void Eventos::setUsarFila(bool b)
{
	usandoFila = b;
}

bool Eventos::estaUsandoFila()
{
	return usandoFila;
}

void Eventos::limparFila()
{
	while(!fila_eventos.empty())
	{
		fila_eventos.pop();
	}
}

bool Eventos::temEventoNaFila()
{
	return !fila_eventos.empty();
}

SDL_Event Eventos::tirarEventoDaFila()
{
	SDL_Event e = fila_eventos.front();
	fila_eventos.pop();
	return e;
}

int Eventos::registrarEventoDeUsuario()
{
	Uint32 tipo = SDL_RegisterEvents(1);
	if (tipo == ((Uint32)-1))
		return -1;

	return tipo;
}

void Eventos::adicionarEventoDeUsuario(int tipo, int codigo, void *dado1, void *dado2)
{
	if (tipo != ((Uint32)-1)) 
	{
		SDL_Event event;
		SDL_zero(event);
		event.type = tipo;
		event.user.code = codigo;
		event.user.data1 = dado1;
		event.user.data2 = dado2;
		SDL_PushEvent(&event);
	}
}