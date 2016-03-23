#include "LinhaTempo.h"



LinhaTempo::LinhaTempo()
{
	tempo = 0;
	indo = true;
	duracao = 3.0f;
	parado = false;
}

LinhaTempo::~LinhaTempo()
{
}

void LinhaTempo::reset()
{
	pos.x = inicio;
	indo = true;
	tempo = 0;
	parado = false;
}

void LinhaTempo::atualizar(float dt)
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

	if (_indo)
		pos.x = uniEaseLinear(t, duracao, inicio, fim - inicio);
	else
		pos.x = uniEaseLinear(t, duracao, fim, inicio - fim);
}

void LinhaTempo::desenhar()
{
	gGraficos.desenharLinha(pos.x, pos.y, pos.x, pos.y + alt, 255, 255, 255, 255);
}
