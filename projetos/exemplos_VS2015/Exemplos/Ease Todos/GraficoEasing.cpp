#include "GraficoEasing.h"



GraficoEasing::GraficoEasing()
{
	easefunc = uniEaseLinear;
	nome = "Linear";
	cor.set(255, 255, 255, 255);
}


GraficoEasing::~GraficoEasing()
{
}

bool GraficoEasing::clicou()
{
	Quad r(pos.x - tam.x / 2, pos.y - tam.y / 2, tam.x, tam.y);
	return (gMouse.pressionou[BOTAO_MOUSE_ESQ] && uniTestarColisaoPontoComRetangulo(gMouse.x, gMouse.y, r));
}

void GraficoEasing::desenhar()
{
	Quad r(pos.x - tam.x / 2, pos.y - tam.y / 2, tam.x, tam.y);

	int p = 0;
	int xMin = r.x + tam.x*0.1;
	int xMax = r.x + tam.x*0.9;
	int yMin = r.y + tam.y*0.9;
	int yMax = r.y + tam.y*0.1;

	int xAnt = xMin;
	int yAnt = yMin;

	int tmax = tam.x;
	for (int t = 0; t <= tmax; ++t)
	{
		int x = uniEaseLinear(t, tmax, xMin, xMax - xMin);
		int y = easefunc(t, tmax, yMin, yMax - yMin);
		gGraficos.desenharLinha(xAnt, yAnt, x, y, cor.r, cor.g, cor.b, cor.a);
		xAnt = x;
		yAnt = y;
	}
		
	gGraficos.desenharRetangulo(r, cor.r, cor.g, cor.b);
	gGraficos.desenharTexto(nome, pos.x, pos.y + (tam.y/2) + 10, cor.r, cor.g, cor.g, cor.a);
}