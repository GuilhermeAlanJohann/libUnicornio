#include "GerenciadorDeEventos.h"
 
GerenciadorDeEventos::GerenciadorDeEventos()
{
	mouse = NULL;
	teclado = NULL;
	joysticks = NULL;
	toques = NULL;
	mixador = NULL;

	sair = false;

	listener = NULL;
	filtroEventosApp = NULL;
}

GerenciadorDeEventos::~GerenciadorDeEventos()
{
}

void GerenciadorDeEventos::atualizar()
{
	janela->limparEventos();
	mouse->atualizar();
	teclado->atualizar();
	joysticks->atualizar();
	toques->atualizar();
	
	SDL_PumpEvents();

	SDL_Event evento;
	while(SDL_PollEvent(&evento))
	{
		if(evento.type == SDL_QUIT)
			sair = true;

		janela->processarEvento(evento);
		mouse->processarEvento(evento);
		teclado->processarEvento(evento);
		joysticks->processarEvento(evento);
		toques->processarEvento(evento);
		mixador->processarEvento(evento);

		if (listener)
			listener->processarEvento(evento);
	}
}

void GerenciadorDeEventos::emitirEventoDeSaida()
{
	SDL_Event event;
	SDL_zero(event);
	event.type = SDL_QUIT;
	SDL_PushEvent(&event);
}

ListenerDeEventos* GerenciadorDeEventos::getListener()
{
	return listener;
}

void GerenciadorDeEventos::setListener(ListenerDeEventos* listener)
{
	this->listener = listener;
}

FiltroDeEventosDeApp* GerenciadorDeEventos::getFiltroDeEventosDeApp()
{
	return filtroEventosApp;
}

void GerenciadorDeEventos::setFiltroDeEventosDeApp(FiltroDeEventosDeApp* filtro)
{
	filtroEventosApp = filtro;
	if(filtro)
		SDL_SetEventFilter(filtrarEventosDeApp, filtroEventosApp);
	else
		SDL_SetEventFilter(NULL, NULL);
}

int GerenciadorDeEventos::registrarEventoDeUsuario()
{
	Uint32 tipo = SDL_RegisterEvents(1);
	if (tipo == ((Uint32)-1))
		return -1;

	return tipo;
}

void GerenciadorDeEventos::adicionarEventoDeUsuario(int tipo, int codigo, void *dado1, void *dado2)
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

std::string GerenciadorDeEventos::getStringDaAreaDeTransferencia()
{
	char* str = SDL_GetClipboardText();
	string s = str;
	SDL_free(str);
	return s;
}

void GerenciadorDeEventos::setStringDaAreaDeTransferencia(std::string s)
{
	SDL_SetClipboardText(s.c_str());
}

bool GerenciadorDeEventos::temStringNaAreaDeTransferencia()
{
	return SDL_HasClipboardText();
}

int GerenciadorDeEventos::filtrarEventosDeApp(void *filtro, SDL_Event *event)
{
	if (!filtro)
		return 1;

	FiltroDeEventosDeApp* filtroEventosApp = (FiltroDeEventosDeApp*)filtro;
	
	switch (event->type)
	{
	case SDL_APP_TERMINATING:
		/* Terminate the app.
		Shut everything down before returning from this function.
		*/
		filtroEventosApp->quandoAppEstaTerminando();
		return 0;
	case SDL_APP_LOWMEMORY:
		/* You will get this when your app is paused and iOS wants more memory.
		Release as much memory as possible.
		*/
		filtroEventosApp->quandoAppEstaComPoucaMemoria();
		return 0;
	case SDL_APP_WILLENTERBACKGROUND:
		/* Prepare your app to go into the background.  Stop loops, etc.
		This gets called when the user hits the home button, or gets a call.
		*/
		filtroEventosApp->quandoAppVaiEntrarEmPlanoDeFundo();
		return 0;
	case SDL_APP_DIDENTERBACKGROUND:
		/* This will get called if the user accepted whatever sent your app to the background.
		If the user got a phone call and canceled it, you'll instead get an    SDL_APP_DIDENTERFOREGROUND event and restart your loops.
		When you get this, you have 5 seconds to save all your state or the app will be terminated.
		Your app is NOT active at this point.
		*/
		filtroEventosApp->quandoAppEntrouEmPlanoDeFundo();
		return 0;
	case SDL_APP_WILLENTERFOREGROUND:
		/* This call happens when your app is coming back to the foreground.
		Restore all your state here.
		*/
		filtroEventosApp->quandoAppVaiEntrarEmPrimeiroPlano();
		return 0;
	case SDL_APP_DIDENTERFOREGROUND:
		/* Restart your loops here.
		Your app is interactive and getting CPU again.
		*/
		filtroEventosApp->quandoAppEntrouEmPrimeiroPlano();
		return 0;
	default:
		/* No special processing, add it to the event queue */
		return 1;
	}
}