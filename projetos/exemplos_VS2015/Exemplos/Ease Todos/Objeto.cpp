#include "Objeto.h"
#include "libUnicornio.h"


Objeto::Objeto()
{
	tempo = 0;
	indo = true;
	parado = false;
	cor.set(255, 255, 255, 255);
	duracao = 3.0f;
}

Objeto::~Objeto()
{
}

void Objeto::reset()
{
	pos = posInicial;
	indo = true;
	tempo = 0;
	parado = false;
}

void Objeto::atualizar(float dt)
{
	tempo += dt;
	float t = tempo;
	bool _indo = indo;

	if (parado)
	{
		if (t >= 1.0f)
		{
			tempo = 0;
			parado = false;
		}
		return;
	}

	if (t >= duracao)
	{
		indo = !indo;
		tempo = 0;
		t = duracao;
		parado = true;
	}

	if(_indo)
		pos.x = grafico->easefunc(t, duracao, posInicial.x, posFinal.x - posInicial.x);
	else
		pos.x = grafico->easefunc(t, duracao, posFinal.x, posInicial.x - posFinal.x);

}

void Objeto::desenhar()
{
	Quad quad( pos.x - tam.x / 2, pos.y - tam.y / 2, tam.x, tam.y );
	gGraficos.desenharRetangulo(quad, cor.r, cor.g, cor.b, cor.a, true);
}