#include "Eventos.h"
#include "libUnicornio.h"

using namespace std;

EventosToque::EventosToque()
{
}

EventosToque::~EventosToque()
{
}

void EventosToque::atualizar()
{
	pressionou.clear();
	soltou.clear();
	moveu.clear();
}

void EventosToque::processarEvento(const SDL_Event& evento)
{
	switch(evento.type)
	{
	case SDL_FINGERDOWN:
		{
		Toque t = gerarToque(evento.tfinger);
		t.tipo = TOQUE_SOLTOU;
		pressionou.push_back(t);
		}
	break;

	case SDL_FINGERUP:
		{
		Toque t = gerarToque(evento.tfinger);
		t.tipo = TOQUE_PRESSIONOU;
		soltou.push_back(t);
		}
	break;

	case SDL_FINGERMOTION:
		{
		Toque t = gerarToque(evento.tfinger);
		t.tipo = TOQUE_MOVEU;
		moveu.push_back(t);
		}
	break;
	}
}

vector<Toque> EventosToque::getTodosToques()
{
	vector<Toque> r;
	r.reserve(pressionou.size() + soltou.size() + moveu.size());
	r.insert(r.end(), pressionou.begin(), pressionou.end());
	r.insert(r.end(), soltou.begin(), soltou.end());
	r.insert(r.end(), moveu.begin(), moveu.end());

	return r;
}

Toque EventosToque::gerarToque(const SDL_TouchFingerEvent& evento)
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

void EventosToque::calcularPosicaoEmPixels(Toque& toque)
{
	toque.x = toque.nx*res_x;
	toque.y = toque.ny*res_y;
	toque.dx = toque.ndx*res_x;
	toque.dy = toque.ndy*res_y;
}

void EventosToque::corrigirPosicaoFullscreen(Toque& toque)
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	float ratio = (float)res_x/(float)res_y;
	float width = h*ratio;
	toque.x = toque.x - (w - width)/2;
	toque.x = toque.x*(res_x/((float)width));
	toque.y = toque.y*((float)res_y/(float)h);

	toque.dx = toque.dx - (w - width)/2;
	toque.dx = toque.dx*(res_x/((float)width));
	toque.dy = toque.dy*((float)res_y/(float)h);
}