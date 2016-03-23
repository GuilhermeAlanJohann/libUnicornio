#include "Global.h"

Global* Global::instancia = 0;
GerenciadorDeTempo* Global::gerenciadorDeTempo = 0;
GerenciadorDeEventos* Global::gerenciadorDeEventos = 0;
GerenciadorDeRecursos* Global::gerenciadorDeRecursos = 0;
GerenciadorDeGraficos* Global::gerenciadorDeGraficos = 0;
GerenciadorDeStrings* Global::gerenciadorDeStrings = 0;
EventosMouse* Global::eventosMouse = 0;
EventosTeclado* Global::eventosTeclado = 0;
EventosJoysticks* Global::eventosJoysticks = 0;
EventosToques* Global::eventosToques = 0;
Janela* Global::janela = 0;
MixadorDeAudios* Global::mixadorDeAudios = 0;
GerenciadorDeMusica* Global::gerenciadorDeMusica = 0;
PainelDeDebug* Global::painelDeDebug = 0;

Global::Global()
{
	instancia = this;
}

Global::~Global()
{
	instancia = 0;
}

void Global::inicializar()
{
	//	só aloca memoria, não chama nenhum metodo de inicializacao dos objetos
	gerenciadorDeTempo = new GerenciadorDeTempo;
	gerenciadorDeEventos = new GerenciadorDeEventos;
	gerenciadorDeRecursos = new GerenciadorDeRecursos;
	gerenciadorDeGraficos = new GerenciadorDeGraficos;
	gerenciadorDeStrings = new GerenciadorDeStrings;

	eventosMouse = new EventosMouse;
	eventosTeclado = new EventosTeclado;
	eventosJoysticks = new EventosJoysticks;
	eventosToques = new EventosToques;

	janela = new Janela;

	mixadorDeAudios = new MixadorDeAudios;
	gerenciadorDeMusica = new GerenciadorDeMusica;

	painelDeDebug = new PainelDeDebug;
}

void Global::finalizar()
{
	//	só desaloca memoria, não chama nenhum metodo de finalizacao dos objetos
	delete gerenciadorDeTempo;
	delete gerenciadorDeEventos;
	delete gerenciadorDeRecursos;
	delete gerenciadorDeGraficos;
	delete gerenciadorDeStrings;
	delete eventosMouse;
	delete eventosTeclado;
	delete eventosJoysticks;
	delete eventosToques;
	delete janela;
	delete mixadorDeAudios;
	delete gerenciadorDeMusica;
	delete painelDeDebug;

	gerenciadorDeTempo = 0;
	gerenciadorDeEventos = 0;
	gerenciadorDeRecursos = 0;
	gerenciadorDeGraficos = 0;
	gerenciadorDeStrings = 0;
	eventosMouse = 0;
	eventosTeclado = 0;
	eventosJoysticks = 0;
	eventosToques = 0;
	janela = 0;
	mixadorDeAudios = 0;
	gerenciadorDeMusica = 0;
	painelDeDebug = 0;
}

Global& Global::getInstancia()
{
	return *getInstanciaPtr();
}

Global* Global::getInstanciaPtr()
{
	return (instancia ? instancia : new Global());
}

GerenciadorDeTempo& Global::getTempo()
{
	return *gerenciadorDeTempo;
}

GerenciadorDeEventos& Global::getEventos()
{
	return *gerenciadorDeEventos;
}

GerenciadorDeRecursos& Global::getRecursos()
{
	return *gerenciadorDeRecursos;
}

GerenciadorDeGraficos& Global::getGraficos()
{
	return *gerenciadorDeGraficos;
}

GerenciadorDeStrings& Global::getStrings()
{
	return *gerenciadorDeStrings;
}

EventosMouse& Global::getMouse()
{
	return *eventosMouse;
}

EventosTeclado& Global::getTeclado()
{
	return *eventosTeclado;
}

EventosJoysticks& Global::getJoysticks()
{
	return *eventosJoysticks;
}

EventosToques& Global::getToques()
{
	return *eventosToques;
}

Janela& Global::getJanela()
{
	return *janela;
}

MixadorDeAudios& Global::getMixador()
{
	return *mixadorDeAudios;
}

GerenciadorDeMusica& Global::getMusica()
{
	return *gerenciadorDeMusica;
}

PainelDeDebug& Global::getPainelDeDebug()
{
	return *painelDeDebug;
}