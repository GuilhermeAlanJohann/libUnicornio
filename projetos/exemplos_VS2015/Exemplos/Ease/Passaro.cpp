#include "Passaro.h"



Passaro::Passaro()
{
}

Passaro::~Passaro()
{
}

void Passaro::inicializar()
{
	//	Inicializa sprite
	spr.setSpriteSheet("bird");
	spr.setEscala(0.15, 0.15);
	spr.setVelocidadeAnimacao(3.0f);

	//	Inicializa posições iniciais e finais
	pos.set(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	posInicio = pos;
	destino = pos;

	//	1) Inicializa as variaveis de tempo
	tempo = 0;
	duracaoMov = 2.0f;
}

void Passaro::atualizar()
{
	//	avançar animação
	spr.avancarAnimacao();

	//	Se clicou com o mouse, 
	if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
	{
		// reseta pos inicial
		posInicio = pos;
		// nova posição de destino
		destino.x = gMouse.x;
		destino.y = gMouse.y;
		//	reseta o tempo
		tempo = 0;		
	}

	//	Se não chegou no destino ainda
	if (pos != destino)
	{
		//	2) Soma o tempo do ultimo frame.
		tempo += gTempo.getDeltaTempo();

		//	3) Se o tempo ultrapassou o tempo máximo (duração),
		//		tempo = duração
		if (tempo >= duracaoMov)
			tempo = duracaoMov;

		//	4) Aplica o easing!
		//		Neste exemplo estamos combinando easings diferentes para x e y para gerar efeito de curva.
		//		Os parâmetros das funcoes de easing são:
		//		1 - O tempo (valor entre 0 e 'duração')
		//		2 - A duração do easing;
		//		3 - O valor inicial
		//		4 - O deslocamento (fim - inicio)
		pos.x = uniEaseInOutQuad(tempo, duracaoMov, posInicio.x, destino.x - posInicio.x);
		pos.y = uniEaseLinear(tempo, duracaoMov, posInicio.y, destino.y - posInicio.y);
	}
}

void Passaro::desenhar()
{
	//	Desenhar
	spr.desenhar(pos.x, pos.y);
}