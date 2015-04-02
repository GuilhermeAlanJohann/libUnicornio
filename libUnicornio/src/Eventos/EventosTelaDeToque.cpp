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
	//	nao eh necessario corrigir a posicao em tela cheia para os eventos de toque
	//corrigirPosicaoFullscreen(t);

	return t;
}

void EventosTelaDeToque::calcularPosicaoEmPixels(Toque& toque)
{
	toque.x = toque.nx*janela.getLarguraTela();
	toque.y = toque.ny*janela.getAlturaTela();
	toque.dx = toque.ndx*janela.getLarguraTela();
	toque.dy = toque.ndy*janela.getAlturaTela();
}

/*
void EventosTelaDeToque::corrigirPosicaoFullscreen(Toque& toque)
{
	if(!janela.estaEmTelaCheia())
		return;

	SDL_Rect display;
	SDL_GetDisplayBounds(0, &display);

	float ratio = (float)janela.getLarguraTela()/(float)janela.getAlturaTela();
	float larguraEscalada;
	float alturaEscalada;
		
	if(janela.getLarguraTela()/(float)display.w < janela.getAlturaTela()/(float)display.h)			//	tarjas nas laterais
	{
		larguraEscalada = display.h*ratio;
		alturaEscalada = larguraEscalada/ratio;	
	}
	else if(janela.getAlturaTela()/(float)display.h < janela.getLarguraTela()/(float)display.w)	//	tarjas em cima e em baixo
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
	toque.x = toque.x*(janela.getLarguraTela()/(float)larguraEscalada);
	
	toque.y = toque.y - (display.h - alturaEscalada)/2;
	toque.y = toque.y*(janela.getAlturaTela()/(float)alturaEscalada);
}*/