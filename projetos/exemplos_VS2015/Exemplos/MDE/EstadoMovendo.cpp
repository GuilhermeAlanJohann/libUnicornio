#include "EstadoMovendo.h"
#include "EstadoParado.h"

EstadoMovendo::EstadoMovendo(Vetor2D p)
{
	//	Pega a posi��o destino do agente,
	//		para saber para onde ele deve andar.
	destino = p;
}

EstadoMovendo::~EstadoMovendo()
{
}

void EstadoMovendo::entrar()
{
	//	2.1) Ao entrar no estado, ajusta a anima��o
	getSprite()->setSpriteSheet("movendo");
	getSprite()->setVelocidadeAnimacao(10.0f);
}

void EstadoMovendo::sair()
{
	//	2.3) Ao sair do estado, n�o precisamos fazer nada
}

void EstadoMovendo::atualizar(float dt)
{
	//	2.2) Durante a atualiza��o...

	//	Avan�ar a anima��o
	getSprite()->avancarAnimacao(dt);

	//	Se pressionou o bot�o esquerdo do mouse,
	if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
	{
		//	Muda o estado para EstadoGirando
		Vetor2D pos(gMouse.x, gMouse.y);
		getAgente()->trocarEstado(new EstadoGirando(pos));
		return;
	}

	//	Vetores de posi��o, dire��o e movimento do agente
	Vetor2D pos = getAgente()->getPos();
	Vetor2D dir = destino - pos;
	Vetor2D mov = dir;
	mov.normalizar();

	float vel = 100.0f;	//	velocidade de movimenta��o;
	mov *= vel*dt;

	Vetor2D dif = destino - getAgente()->getPos();
	
	//	Se chegou perto do destino,
	if (mov.comprimento() > dif.comprimento())
	{
		//	Muda a posi��o para o destino e
		//	troca o estado para EstadoParado.
		getAgente()->setPos(destino);
		getAgente()->trocarEstado(new EstadoParado());
	}
	else
	{
		//	Se n�o, continua movendo.
		getAgente()->setPos(pos + mov);
	}
	
}
