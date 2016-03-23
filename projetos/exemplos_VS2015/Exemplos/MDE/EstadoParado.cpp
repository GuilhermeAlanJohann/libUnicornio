#include "EstadoParado.h"



EstadoParado::EstadoParado()
{
}

EstadoParado::~EstadoParado()
{
}

void EstadoParado::entrar()
{
	//	2.1) Ao entrar no estado, ajusta a anima��o
	getSprite()->setSpriteSheet("parado");
	getSprite()->setVelocidadeAnimacao(10.0f);
}

void EstadoParado::sair()
{
	//	2.3) Ao sair do estado, n�o precisamos fazer nada
}

void EstadoParado::atualizar(float dt)
{
	//	2.2) Durante a atualiza��o...

	//	Avan�ar a anima��o
	getSprite()->avancarAnimacao(dt);

	//	Se pressiou o bot�o esquerdo do mouse,
	if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
	{
		//	Muda para o estado "Girando"
		//		Neste caso, estamos passando o posi��o do mouse como 
		//		par�metro para o contrutor do estado, pois queremos que
		//		o agente gire para essa posi��o durante o estado girando.
		Vetor2D pos(gMouse.x, gMouse.y);
		getAgente()->trocarEstado(new EstadoGirando(pos));
	}
}