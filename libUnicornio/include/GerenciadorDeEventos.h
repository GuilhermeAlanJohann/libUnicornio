#ifndef UNI_GERENCIADORDEEVENTOS_H
#define UNI_GERENCIADORDEEVENTOS_H

#include "uniAPI.h"
#include "ListenerDeEventos.h"
#include "FiltroDeEventosDeApp.h"
#include "EventosJoysticks.h"
#include "EventosMouse.h"
#include "EventosTeclado.h"
#include "EventosToques.h"
#include "MixadorDeAudios.h"
#include "Janela.h"

class UNI_API GerenciadorDeEventos
{
public: 
	GerenciadorDeEventos();
	~GerenciadorDeEventos();

	void atualizar();

	void emitirEventoDeSaida();

	ListenerDeEventos* getListener();
	void setListener(ListenerDeEventos* listener);

	FiltroDeEventosDeApp* getFiltroDeEventosDeApp();
	void setFiltroDeEventosDeApp(FiltroDeEventosDeApp* filtro);

	int registrarEventoDeUsuario();
	void adicionarEventoDeUsuario(int tipo, int codigo = 0, void *dado1 = NULL, void *dado2 = NULL);

	std::string getStringDaAreaDeTransferencia();
	void setStringDaAreaDeTransferencia(std::string s);
	bool temStringNaAreaDeTransferencia();

	Janela *janela;
	EventosMouse *mouse;
	EventosTeclado *teclado;
	EventosJoysticks *joysticks;
	EventosToques *toques;
	MixadorDeAudios *mixador;

	bool sair;	//	variavel para saber se o evento de saída foi emitido

private:
	ListenerDeEventos* listener;

	FiltroDeEventosDeApp* filtroEventosApp;
	static int filtrarEventosDeApp(void *userdata, SDL_Event *event);	//	callback que roda em outra thread
};

#endif