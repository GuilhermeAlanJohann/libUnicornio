#include "GerenciadorDeTempo.h"

GerenciadorDeTempo::GerenciadorDeTempo()
{
	limiteFPS = 0;
	deltaTempoUs = 0;
	tickAntes = 0;
	tickAtual = 0;
}

GerenciadorDeTempo::~GerenciadorDeTempo()
{
}

void GerenciadorDeTempo::inicializar()
{
	limiteFPS = 60;	//	60 frames por segundo
	deltaTempoUs = 0;
	tickAntes = SDL_GetPerformanceCounter();
	tickAtual = tickAntes;
}

void GerenciadorDeTempo::finalizar()
{
	limiteFPS = 0;
	deltaTempoUs = 0;
	tickAntes = 0;
	tickAtual = 0;
}

void GerenciadorDeTempo::atualizar(bool limitarFPS)
{
	Uint64 framerateUs = (Uint64)(1000000.0 / limiteFPS);

	tickAtual = SDL_GetPerformanceCounter();	// tempo em counts
	deltaTempoUs = (1000000 * (tickAtual - tickAntes)) / SDL_GetPerformanceFrequency();	//	deltaTempo em microsegundos

	if ((deltaTempoUs < framerateUs) && (limitarFPS))
	{
		int delay = (int)framerateUs - (int)deltaTempoUs;	// delay em microsegundos
		while (delay > 0)
		{
			if (delay > 1000)
				SDL_Delay(1);

			deltaTempoUs = (1000000 * (SDL_GetPerformanceCounter() - tickAntes)) / SDL_GetPerformanceFrequency();	//	deltaTempo em microsegundos
			delay = (int)(framerateUs - deltaTempoUs);
		}
	}

	tickAntes = tickAtual;
}

Uint64 GerenciadorDeTempo::getTicks()
{
	return SDL_GetPerformanceCounter();
}

double GerenciadorDeTempo::getTempoEntreTicks(Uint64 ticksInicio, Uint64 ticksFim)
{
	return ((double)(ticksFim - ticksInicio)) / (double)SDL_GetPerformanceFrequency();
}

double GerenciadorDeTempo::getTempoAteTickAtual(Uint64 ticksAnterior)
{
	return getTempoEntreTicks(ticksAnterior, SDL_GetPerformanceCounter());
}

double GerenciadorDeTempo::getFPS()
{
	return 1000000.0 / (double)deltaTempoUs;
}

Uint32 GerenciadorDeTempo::getLimiteFPS()
{
	return limiteFPS;
}

Uint64 GerenciadorDeTempo::getDeltaTempoEmMicrosegundos()
{
	return deltaTempoUs;
}

double GerenciadorDeTempo::getDeltaTempoEmMilisegundos()
{
	//	converte para milisegundos
	return ((double)deltaTempoUs) / 1000.0;
}

double GerenciadorDeTempo::getDeltaTempo()
{
	//	converte para segundos
	return ((double)deltaTempoUs) / 1000000.0;
}

void GerenciadorDeTempo::setLimiteFPS(Uint32 limiteFPS)
{
	this->limiteFPS = limiteFPS;
}