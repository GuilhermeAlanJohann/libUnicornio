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

	//	O resto da inicializa��o vem aqui!
	//	...

	//	1)	Carrega a textura
	gRecursos.carregarTextura("fundo", "assets/comum/fundo2.png");

	//		Ou carrega a textura e j� pega o ponteiro pra ela
	//t = gRecursos.carregarTextura("fundo", "assets/comum/fundo2.png");
}

void Jogo::finalizar()
{
	//	O resto da finaliza��o vem aqui (provavelmente, em ordem inversa a inicializa��o)!
	//	...

	//	4)	Descarrega todos os recursos
	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	Seu c�digo vem aqui!
		//	...

		//	2)	Pega o ponteiro para a textura (n�o � necess�rio se j� pegou quando carregou a textura)
		Textura* t = gRecursos.getTextura("fundo");

		//	3)	Desenha a textura
		//	Desenha a textura completa
		t->desenhar(150, 150);

		//	Desenha um retangulo da textura em um retangulo destino
		Quad retan(100, 100, 40, 30);
		Quad dest(350, 50, 200, 150);
		t->desenhar(retan, dest);

		//	Desenha passando todos os par�metros
		Vetor2D pos(150, 450);
		float rot = 0;
		Vetor2D ancora(0.5, 0.5);
		Vetor2D escala(1.0, 1.0);
		Cor cor(255, 255, 255, 128); //	meio transparente
		EnumInverterDesenho inverter = INVERTER_XY;		//	outros valores s�o: NAO_INVERTER, INVERTER_X, INVERTER_Y
		t->desenhar(pos.x, pos.y, rot, ancora, escala, cor, inverter);

		//	Desenha um retangulo da textura passando todos os par�metros
		pos.x += 300;
		t->desenhar(retan, pos.x, pos.y, rot, ancora, escala, cor, inverter);

		uniTerminarFrame();
	}
}