#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(800, 600, false);

	//	O resto da inicialização vem aqui!
	//	...

	int tam = 60;
	int x = 20 + tam/2;
	int dx = tam + 10;
	for (int i = 0; i < MAX_FUNCS_EASING; ++i)
	{
		botoes[i].pos.set(x, gJanela.getAltura()*0.15);
		botoes[i].tam.set(tam, tam);
		x += dx;
	}

	botoes[0].easefunc = uniEaseLinear;
	botoes[1].easefunc = uniEaseInSin;
	botoes[2].easefunc = uniEaseInQuad;
	botoes[3].easefunc = uniEaseInCub;
	botoes[4].easefunc = uniEaseInQuart;
	botoes[5].easefunc = uniEaseInQuint;
	botoes[6].easefunc = uniEaseInExpo;
	botoes[7].easefunc = uniEaseInCirc;
	botoes[8].easefunc = uniEaseInBack;
	botoes[9].easefunc = uniEaseInElastic;
	botoes[10].easefunc = uniEaseInBounce;

	botoes[0].nome = "Linear";
	botoes[1].nome = "Sin";
	botoes[2].nome = "Quad";
	botoes[3].nome = "Cub";
	botoes[4].nome = "Quart";
	botoes[5].nome = "Quint";
	botoes[6].nome = "Expo";
	botoes[7].nome = "Circ";
	botoes[8].nome = "Back";
	botoes[9].nome = "Elastic";
	botoes[10].nome = "Bounce";

	atual = 0; 
	botoes[atual].cor.set(255, 0, 0, 255);

	retan.x = 150;
	retan.y = botoes[0].pos.y + 70;
	retan.larg = gJanela.getLargura() - retan.x - 30;
	retan.alt = gJanela.getAltura() - retan.y - 30;

	for (int i = 0; i < 3; ++i)
	{
		tipos[i] = botoes[atual];
		tipos[i].pos.x = retan.x - 70;
		tipos[i].pos.y = retan.y + (retan.alt*(i + 1)*0.25);
		tipos[i].cor.set(255, 255, 255, 255);
	}
	tipos[0].nome = "In";
	tipos[1].nome = "InOut";
	tipos[2].nome = "Out";

	duracaoMov = 3.0f;

	for (int i = 0; i < 3; ++i)
	{
		objetos[i].grafico = &tipos[i];
		objetos[i].tam.set(50, 50);
		objetos[i].posInicial.set(retan.x + objetos[i].tam.x/2, tipos[i].pos.y);
		objetos[i].posFinal.set(retan.x + retan.larg - objetos[i].tam.x/2, tipos[i].pos.y);
		objetos[i].duracao = duracaoMov;
		objetos[i].reset();
	}
	objetos[0].cor.set(255, 0, 0, 255);
	objetos[1].cor.set(0, 255, 0, 255);
	objetos[2].cor.set(0, 0, 255, 255);

	linha.alt = retan.alt;
	linha.inicio = objetos[0].posInicial.x;
	linha.fim = objetos[0].posFinal.x;
	linha.pos.set(linha.inicio, retan.y);
	linha.duracao = duracaoMov;
	linha.reset();
}

void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!
	//	...

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	Seu código vem aqui!
		//	...
		for (int i = 0; i < MAX_FUNCS_EASING; ++i)
		{
			if (botoes[i].clicou())
			{
				botoes[atual].cor.set(255, 255, 255, 255);
				botoes[i].cor.set(255, 0, 0, 255);
				atual = i;

				for (int i = 0; i < 3; ++i)
				{
					setEaseFuncsTipos();
					tipos[i].cor.set(255, 255, 255, 255);
					objetos[i].reset();
					linha.reset();
				}
			}

			botoes[i].desenhar();
		}

		linha.atualizar(gTempo.getDeltaTempo());

		for (int i = 0; i < 3; ++i)
		{
			tipos[i].desenhar();
			objetos[i].atualizar(gTempo.getDeltaTempo());
			objetos[i].desenhar();
		}
		
		linha.desenhar();
		gGraficos.desenharRetangulo(retan, 255, 255, 255);

		uniTerminarFrame();
	}
}

void Jogo::setEaseFuncsTipos()
{
	switch (atual)
	{
	case 0:
		tipos[0].easefunc = uniEaseInLinear;
		tipos[2].easefunc = uniEaseOutLinear;
		tipos[1].easefunc = uniEaseInOutLinear;
		break;

	case 1:
		tipos[0].easefunc = uniEaseInSin;
		tipos[2].easefunc = uniEaseOutSin;
		tipos[1].easefunc = uniEaseInOutSin;
		break;

	case 2:
		tipos[0].easefunc = uniEaseInQuad;
		tipos[2].easefunc = uniEaseOutQuad;
		tipos[1].easefunc = uniEaseInOutQuad;
		break;

	case 3:
		tipos[0].easefunc = uniEaseInCub;
		tipos[1].easefunc = uniEaseOutCub;
		tipos[2].easefunc = uniEaseInOutCub;
		break;

	case 4:
		tipos[0].easefunc = uniEaseInQuart;
		tipos[2].easefunc = uniEaseOutQuart;
		tipos[1].easefunc = uniEaseInOutQuart;
		break;

	case 5:
		tipos[0].easefunc = uniEaseInQuint;
		tipos[2].easefunc = uniEaseOutQuint;
		tipos[1].easefunc = uniEaseInOutQuint;
		break;

	case 6:
		tipos[0].easefunc = uniEaseInExpo;
		tipos[2].easefunc = uniEaseOutExpo;
		tipos[1].easefunc = uniEaseInOutExpo;
		break;

	case 7:
		tipos[0].easefunc = uniEaseInCirc;
		tipos[2].easefunc = uniEaseOutCirc;
		tipos[1].easefunc = uniEaseInOutCirc;
		break;

	case 8:
		tipos[0].easefunc = uniEaseInBack;
		tipos[2].easefunc = uniEaseOutBack;
		tipos[1].easefunc = uniEaseInOutBack;
		break;

	case 9:
		tipos[0].easefunc = uniEaseInElastic;
		tipos[2].easefunc = uniEaseOutElastic;
		tipos[1].easefunc = uniEaseInOutElastic;
		break;

	case 10:
		tipos[0].easefunc = uniEaseInBounce;
		tipos[2].easefunc = uniEaseOutBounce;
		tipos[1].easefunc = uniEaseInOutBounce;
		break;

	default:
		tipos[0].easefunc = uniEaseInLinear;
		tipos[2].easefunc = uniEaseOutLinear;
		tipos[1].easefunc = uniEaseInOutLinear;
	}
}