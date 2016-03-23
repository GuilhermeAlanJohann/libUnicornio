#include "EstadoMovendo.h"
#include "EstadoParado.h"

EstadoMovendo::EstadoMovendo(Vetor2D p)
{
	//	Pega a posição destino do agente,
	//		para saber para onde ele deve andar.
	destino = p;
}

EstadoMovendo::~EstadoMovendo()
{
}

void EstadoMovendo::entrar()
{
	//	2.1) Ao entrar no estado, ajusta a animação
	getSprite()->setSpriteSheet("movendo");
	getSprite()->setVelocidadeAnimacao(10.0f);
}

void EstadoMovendo::sair()
{
	//	2.3) Ao sair do estado, não precisamos fazer nada
}

void EstadoMovendo::atualizar(float dt)
{
	//	2.2) Durante a atualização...

	//	Avançar a animação
	getSprite()->avancarAnimacao(dt);

	//	Se pressionou o botão esquerdo do mouse,
	if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
	{
		//	Muda o estado para EstadoGirando
		Vetor2D pos(gMouse.x, gMouse.y);
		getAgente()->trocarEstado(new EstadoGirando(pos));
		return;
	}

	//	Vetores de posição, direção e movimento do agente
	Vetor2D pos = getAgente()->getPos();
	Vetor2D dir = destino - pos;
	Vetor2D mov = dir;
	mov.normalizar();

	float vel = 100.0f;	//	velocidade de movimentação;
	mov *= vel*dt;

	Vetor2D dif = destino - getAgente()->getPos();
	
	//	Se chegou perto do destino,
	if (mov.comprimento() > dif.comprimento())
	{
		//	Muda a posição para o destino e
		//	troca o estado para EstadoParado.
		getAgente()->setPos(destino);
		getAgente()->trocarEstado(new EstadoParado());
	}
	else
	{
		//	Se não, continua movendo.
		getAgente()->setPos(pos + mov);
	}
	
}
