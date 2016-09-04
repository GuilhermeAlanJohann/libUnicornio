#include "EventosMouse.h"
#include "Global.h"
#include <algorithm>

EventosMouse::EventosMouse()
{
	for(int i = 0; i < NUMERO_DE_BOTOES_MOUSE; ++i)
	{
		pressionou[i] = false;
		segurando[i] = false;
		soltou[i] = false;
	}

	x = 0;
	y = 0;
	dx = 0;
	dy = 0;
	nx = 0.0f;
	ny = 0.0f;
	ndx = 0.0f;
	ndy = 0.0f;
	roda = 0;

	limitandoPos = true;
}

EventosMouse::~EventosMouse()
{

}

void EventosMouse::atualizar()
{
	// zerar inputs
	for(int i = 0; i < NUMERO_DE_BOTOES_MOUSE; ++i)
	{
		pressionou[i] = false;
		soltou[i] = false;
	}
	dx = 0;
	dy = 0;
	ndx = 0.0f;
	ndy = 0.0f;
	roda = 0;

	// calcular posicao do mouse (por isso aqui, não precisamos do responder ao evento SDL_MOUSEMOTION;
	int xAnt = x;
	int yAnt = y;
	float nxAnt = nx;
	float nyAnt = ny;

	SDL_GetMouseState(&x, &y);
	corrigirPosicao();
	if (limitandoPos)
		limitarPosicao();
	nx = (float)x/(float)gJanela.getLargura();
	ny = (float)y/(float)gJanela.getAltura();

	dx = x - xAnt;
	dy = y - yAnt;
	ndx = nx - nxAnt;
	ndy = ny - nyAnt;
}

void EventosMouse::processarEvento(const SDL_Event& evento)
{
    switch(evento.type)
    {
		/*
	case SDL_MOUSEMOTION:	// Responder a esse case não é necessario, mas caso seja futuramente...
		{
		int xAnt = x;
		int yAnt = y;
		float nxAnt = nx;
		float nyAnt = ny;

		x = evento.button.x;
		y = evento.button.y;
		nx = (float)x/(float)janela.getLargura();
		ny = (float)y/(float)janela.getAltura();

		//	deve-se somar, pois este evento pode ocorrer mais de uma vez em um mesmo frame;
		dx += x - xAnt;
		dy += y - yAnt;
		ndx += nx - nxAnt;
		ndy += ny - nyAnt;

		}
		break;
		*/
	case SDL_MOUSEBUTTONDOWN:

		segurando[evento.button.button -1] = true;

		if(evento.button.state == SDL_PRESSED)
		{
			pressionou[evento.button.button -1] = true;
		}
			
		break;

	case SDL_MOUSEBUTTONUP:

		segurando[evento.button.button -1] = false;

		if(evento.button.state == SDL_RELEASED)
		{
			soltou[evento.button.button -1] = true;
		}

		break;

	case SDL_MOUSEWHEEL:

		//	deve-se somar, pois este evento pode ocorrer mais de uma vez em um mesmo frame;
		roda += evento.wheel.y;

		break;
	}
}

void EventosMouse::corrigirPosicao()
{
	int jLarg, jAlt;
	gJanela.obterTamanho(jLarg, jAlt);
	int jLargReal, jAltReal;
	gJanela.obterTamanhoReal(jLargReal, jAltReal);
	float razao = (float)jLarg / (float)jAlt;
	float razaoLarg = jLarg / (float)jLargReal;
	float razaoAlt = jAlt / (float)jAltReal;

	if (razaoLarg < razaoAlt)		//	tarjas pretas nas laterais 
	{
		float largEscalada = jAltReal * razao;
		x = (x - (jLargReal - largEscalada) / 2.0f) * razaoAlt;
		y *= razaoAlt;
	}
	else if (razaoAlt < razaoLarg)	// tarjas pretas em cima e em baixo
	{
		float altEscalada = jLargReal / razao;
		x *= razaoLarg;
		y = (y - (jAltReal - altEscalada) / 2.0f) * razaoLarg;
	}
	else	//	sem tarjas pretas
	{
		x *= razaoLarg;
		y *= razaoAlt;
	}
}

void EventosMouse::limitarPosicao()
{
	int minx = 0;
	int miny = 0;
	int maxx = minx + gJanela.getLargura();
	int maxy = miny + gJanela.getAltura();

	x = max(minx, x);
	y = max(miny, y);

	x = min(maxx, x);
	y = min(maxy, y);
}

void EventosMouse::esconderCursor()
{
	SDL_ShowCursor(0);
}

void EventosMouse::mostrarCursor()
{
	SDL_ShowCursor(1);
}

void EventosMouse::posicionarEm(int x, int y)
{
	int jLarg, jAlt;
	gJanela.obterTamanho(jLarg, jAlt);

	this->x = x;
	this->y = y;
	nx = (float)x/(float)jLarg;
	ny = (float)y/(float)jAlt;

	int jLargReal, jAltReal;
	gJanela.obterTamanhoReal(jLargReal, jAltReal);
	float razao = (float)jLarg / (float)jAlt;
	float razaoLarg = jLarg / (float)jLargReal;
	float razaoAlt = jAlt / (float)jAltReal;

	if (razaoLarg < razaoAlt)		//	tarjas pretas nas laterais 
	{
		float largEscalada = jAltReal * razao;
		float largTarja = (jLargReal - largEscalada) / 2.0f;
		x = largTarja + (x / razaoAlt);
		y /= razaoAlt;
	}
	else if (razaoAlt < razaoLarg)	// tarjas pretas em cima e em baixo
	{
		float altEscalada = jLargReal / razao;
		float altTarja = (jAltReal - altEscalada) / 2.0f;
		x /= razaoLarg;
		y = altTarja + (y / razaoLarg);
	}
	else	//	sem tarjas pretas
	{
		x /= razaoLarg;
		y /= razaoAlt;
	}

	SDL_WarpMouseInWindow(gJanela.getSDL_Window(), x, y);

	limitarPosicao();
}

bool EventosMouse::estaLimitandoPosicao()
{
	return limitandoPos;
}

void EventosMouse::setLimitandoPosicao(bool limitar)
{
	limitandoPos = limitar;
}