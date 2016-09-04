#ifndef UNI_GLOBAL_H
#define UNI_GLOBAL_H

#include "uniAPI.h"
#include "GerenciadorDeTempo.h"
#include "GerenciadorDeEventos.h"
#include "GerenciadorDeRecursos.h"
#include "GerenciadorDeGraficos.h"
#include "GerenciadorDeStrings.h"
#include "Janela.h"
#include "MixadorDeAudios.h"
#include "GerenciadorDeMusica.h"
#include "PainelDeDebug.h"

class UNI_API Global
{
public:
	~Global();

	static void inicializar();
	static void finalizar();

	static Global& getInstancia();
	static Global* getInstanciaPtr();

	static GerenciadorDeTempo& getTempo();
	static GerenciadorDeEventos& getEventos();
	static GerenciadorDeRecursos& getRecursos();
	static GerenciadorDeGraficos& getGraficos();
	static GerenciadorDeStrings& getStrings();

	static EventosMouse& getMouse();
	static EventosTeclado& getTeclado();
	static EventosJoysticks& getJoysticks();
	static EventosToques& getToques();
	
	static Janela& getJanela();
	
	static MixadorDeAudios& getMixador();
	static GerenciadorDeMusica& getMusica();

	static PainelDeDebug& getPainelDeDebug();

private:
	Global();

	static Global* instancia;

	static GerenciadorDeTempo* gerenciadorDeTempo;
	static GerenciadorDeEventos* gerenciadorDeEventos;
	static GerenciadorDeRecursos* gerenciadorDeRecursos;
	static GerenciadorDeGraficos* gerenciadorDeGraficos;
	static GerenciadorDeStrings* gerenciadorDeStrings;

	static EventosMouse* eventosMouse;
	static EventosTeclado* eventosTeclado;
	static EventosJoysticks* eventosJoysticks;
	static EventosToques* eventosToques;

	static Janela* janela;

	static MixadorDeAudios* mixadorDeAudios;
	static GerenciadorDeMusica* gerenciadorDeMusica;

	static PainelDeDebug* painelDeDebug;
};

//	defines para facilitar o uso
#define gTempo Global::getTempo()
#define gEventos Global::getEventos()
#define gRecursos Global::getRecursos()
#define gGraficos Global::getGraficos()
#define gStrings Global::getStrings()

#define gMouse Global::getMouse()
#define gTeclado Global::getTeclado()
#define gJoysticks Global::getJoysticks()
#define gToques Global::getToques()

#define gJanela Global::getJanela()

#define gAudios Global::getMixador()
#define gMusica Global::getMusica()

#define gDebug Global::getPainelDeDebug()

#endif