#include "Eventos.h"
#include "libUnicornio.h"

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

	// calcular posicao do mouse (por isso aqui, n�o precisamos do responder ao evento SDL_MOUSEMOTION;
	int xAnt = x;
	int yAnt = y;
	float nxAnt = nx;
	float nyAnt = ny;

	SDL_GetMouseState(&x, &y);
	corrigirPosicaoFullscreen();
	nx = (float)x/(float)res_x;
	ny = (float)y/(float)res_y;

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
	case SDL_MOUSEMOTION:	// Responder a esse case n�o � necessario, mas caso seja futuramente...
		{
		int xAnt = x;
		int yAnt = y;
		float nxAnt = nx;
		float nyAnt = ny;

		x = evento.button.x;
		y = evento.button.y;
		nx = (float)x/(float)res_x;
		ny = (float)y/(float)res_y;

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

void EventosMouse::corrigirPosicaoFullscreen()
{
	if(!uniEstaEmModoTelaCheia())
		return;

	SDL_Rect display;
	SDL_GetDisplayBounds(0, &display);

	float ratio = (float)res_x/(float)res_y;
	float larguraEscalada;
	float alturaEscalada;
		
	if(res_x/(float)display.w < res_y/(float)display.h)			//	tarjas nas laterais
	{
		larguraEscalada = display.h*ratio;
		alturaEscalada = larguraEscalada/ratio;	
	}
	else if(res_y/(float)display.h < res_x/(float)display.w)	//	tarjas em cima e em baixo
	{
		alturaEscalada = display.w/ratio;
		larguraEscalada = alturaEscalada*ratio;
	}
	else	//	sem tarjas
	{
		larguraEscalada = display.h*ratio;
		alturaEscalada = display.w/ratio;
	}

	x = x - (display.w - larguraEscalada)/2;
	x = x*(res_x/(float)larguraEscalada);
	
	y = y - (display.h - alturaEscalada)/2;
	y = y*(res_y/(float)alturaEscalada);
}

void EventosMouse::mostrarCursor(bool mostrar)
{
	if(mostrar)
	{
		SDL_ShowCursor(1);
	}
	else
	{
		SDL_ShowCursor(0);
	}
}

void EventosMouse::posicionarEm(int x, int y)
{
	this->x = x;
	this->y = y;
	SDL_WarpMouseInWindow(window, x, y);
	nx = (float)x/(float)res_x;
	ny = (float)y/(float)res_y;
}