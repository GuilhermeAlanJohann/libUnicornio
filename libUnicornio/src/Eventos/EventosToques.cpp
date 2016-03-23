#include "EventosToques.h"
#include "Global.h"
#include <algorithm>

using namespace std;

EventosToques::EventosToques()
{
	limitandoPos = true;
}

EventosToques::~EventosToques()
{
}

void EventosToques::atualizar()
{
	pressionou.clear();
	soltou.clear();
	moveu.clear();
}

void EventosToques::processarEvento(const SDL_Event& evento)
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

vector<Toque> EventosToques::getTodosToques()
{
	vector<Toque> r;
	r.reserve(pressionou.size() + segurando.size() + soltou.size() + moveu.size());
	r.insert(r.end(), pressionou.begin(), pressionou.end());
	r.insert(r.end(), segurando.begin(), segurando.end());
	r.insert(r.end(), soltou.begin(), soltou.end());
	r.insert(r.end(), moveu.begin(), moveu.end());

	return r;
}

bool EventosToques::estaLimitandoPosicao()
{
	return limitandoPos;
}

void EventosToques::setLimitandoPosicao(bool limitar)
{
	limitandoPos = limitar;
}

Toque EventosToques::gerarToque(const SDL_TouchFingerEvent& evento)
{
	Toque t;

	t.pressao = evento.pressure;
	t.idDedo = evento.fingerId;

	t.nx = evento.x;
	t.ny = evento.y;
	t.ndx = evento.dx;
	t.ndy = evento.dy;

	calcularPosicaoEmPixels(t);
	//	nao eh necessario corrigir a posicao em tela cheia para os eventos de toque
	//corrigirPosicaoFullscreen(t);
	if (limitandoPos)
		limitarPosicao(t);

	return t;
}

void EventosToques::calcularPosicaoEmPixels(Toque& toque)
{
	toque.x = toque.nx*gJanela.getLargura();
	toque.y = toque.ny*gJanela.getAltura();
	toque.dx = toque.ndx*gJanela.getLargura();
	toque.dy = toque.ndy*gJanela.getAltura();
}

/*
void EventosToques::corrigirPosicaoFullscreen(Toque& toque)
{
	if(!janela.estaEmTelaCheia())
		return;

	SDL_Rect display;
	SDL_GetDisplayBounds(0, &display);

	float ratio = (float)janela.getLargura()/(float)janela.getAltura();
	float larguraEscalada;
	float alturaEscalada;
		
	if(janela.getLargura()/(float)display.w < janela.getAltura()/(float)display.h)			//	tarjas nas laterais
	{
		larguraEscalada = display.h*ratio;
		alturaEscalada = larguraEscalada/ratio;	
	}
	else if(janela.getAltura()/(float)display.h < janela.getLargura()/(float)display.w)	//	tarjas em cima e em baixo
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
	toque.x = toque.x*(janela.getLargura()/(float)larguraEscalada);
	
	toque.y = toque.y - (display.h - alturaEscalada)/2;
	toque.y = toque.y*(janela.getAltura()/(float)alturaEscalada);
}*/

void EventosToques::limitarPosicao(Toque& toque)
{
	int minx = 0;
	int miny = 0;
	int maxx = minx + gJanela.getLargura();
	int maxy = miny + gJanela.getAltura();

	toque.x = max(minx, toque.x);
	toque.y = max(miny, toque.y);

	toque.x = min(maxx, toque.x);
	toque.y = min(maxy, toque.y);
}