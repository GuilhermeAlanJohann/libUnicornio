#include "Eventos.h"
#include "libUnicornio.h"

using namespace std;

EventosTelaDeToque::EventosTelaDeToque()
{
}

EventosTelaDeToque::~EventosTelaDeToque()
{
}

void EventosTelaDeToque::atualizar()
{
	pressionou.clear();
	soltou.clear();
	moveu.clear();
}

void EventosTelaDeToque::processarEvento(const SDL_Event& evento)
{
	switch(evento.type)
	{
	case SDL_FINGERDOWN:
		{
		Toque t = gerarToque(evento.tfinger);
		t.tipo = TOQUE_PRESSIONOU;
		pressionou.push_back(t);
		t.tipo = TOQUE_SEGURANDO;
		segurando.push_back(t);
		}
	break;

	case SDL_FINGERUP:
		{
		Toque t = gerarToque(evento.tfinger);
		t.tipo = TOQUE_SOLTOU;
		soltou.push_back(t);
		for(unsigned int i = 0; i < segurando.size(); ++i)
			if(segurando[i].idDedo == t.idDedo)
				segurando.erase(segurando.begin() + i);
		}
	break;

	case SDL_FINGERMOTION:
		{
		Toque t = gerarToque(evento.tfinger);
		t.tipo = TOQUE_MOVEU;
		moveu.push_back(t);
		for(unsigned int i = 0; i < segurando.size(); ++i)
			if(segurando[i].idDedo == t.idDedo)
			{
				segurando[i] = t;
				segurando[i].tipo = TOQUE_SEGURANDO;
			}
		}
	break;
	}
}

vector<Toque> EventosTelaDeToque::getTodosToques()
{
	vector<Toque> r;
	r.reserve(pressionou.size() + segurando.size() + soltou.size() + moveu.size());
	r.insert(r.end(), pressionou.begin(), pressionou.end());
	r.insert(r.end(), segurando.begin(), segurando.end());
	r.insert(r.end(), soltou.begin(), soltou.end());
	r.insert(r.end(), moveu.begin(), moveu.end());

	return r;
}

Toque EventosTelaDeToque::gerarToque(const SDL_TouchFingerEvent& evento)
{
	Toque t;

	t.pressao = evento.pressure;
	t.idDedo = evento.fingerId;

	t.nx = evento.x;
	t.ny = evento.y;
	t.ndx = evento.dx;
	t.ndy = evento.dy;

	calcularPosicaoEmPixels(t);
	corrigirPosicaoFullscreen(t);

	return t;
}

void EventosTelaDeToque::calcularPosicaoEmPixels(Toque& toque)
{
	toque.x = toque.nx*res_x;
	toque.y = toque.ny*res_y;
	toque.dx = toque.ndx*res_x;
	toque.dy = toque.ndy*res_y;
}

void EventosTelaDeToque::corrigirPosicaoFullscreen(Toque& toque)
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

	toque.x = toque.x - (display.w - larguraEscalada)/2;
	toque.x = toque.x*(res_x/(float)larguraEscalada);
	
	toque.y = toque.y - (display.h - alturaEscalada)/2;
	toque.y = toque.y*(res_y/(float)alturaEscalada);
}