#include "EstadoGirando.h"
#include "EstadoMovendo.h"


EstadoGirando::EstadoGirando(Vetor2D p)
{
	//	Pega a posi��o destino do agente,
	//		para saber para onde ele deve girar.
	destino = p;
}

EstadoGirando::~EstadoGirando()
{
}

void EstadoGirando::entrar()
{
	//	2.1) Ao entrar no estado, ajusta a anima��o
	getSprite()->setSpriteSheet("movendo");
	getSprite()->setVelocidadeAnimacao(10.0f);
}

void EstadoGirando::sair()
{
	//	2.3) Ao sair do estado, n�o precisamos fazer nada
}

void EstadoGirando::atualizar(float dt)
{
	//	2.2) Durante a atualiza��o...

	//	Avan�ar a anima��o
	getSprite()->avancarAnimacao(dt);

	//	Se pressiou o bot�o esquerdo do mouse,
	if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
	{
		//	Muda o destino.
		destino.set(gMouse.x, gMouse.y);
	}

	float rot = getAgente()->getRot();
	float vel = 90.0f;	//	velocidade de rota��o

	//	Dire��o do agente
	Vetor2D dir(1, 0);
	dir.rotacionar(rot);

	//	Dire��o que o agente deve ir
	Vetor2D dirDestino = destino - getAgente()->getPos();
	float rotDestino = dirDestino.getAngulo();

	//	Angulo entre o vetor de dire��o e o vetor de dire��o destino
	float ang = dir.getAnguloAteVetor(dirDestino);

	//	Se a rota��o est� muito pr�xima,
	if (fabsf(ang) < vel*dt)
	{
		//	for�a a rota��o para o destino
		rot = rotDestino;
		//	Terminou a rota��o
		//	Muda o estado (EstadoMovendo)
		getAgente()->trocarEstado(new EstadoMovendo(destino));
	}
	else	//	Se n�o, aplica a rota��o segundo a velocidade
	{
		float sinal = 1.0f;	// sinal da rota��o (-1 ou +1);
		if (ang < 0)
			sinal = -1.0f;

		//	Multiplica a velocidade de rota��o pelo tempo,
		//	para saber a velocidade em um frame.
		//	Multiplica pelo sinal para saber qual o lado da rota��o
		//	Soma isso a rota��o
		rot += vel*dt*sinal;
	}

	//	Aplica a nova rota��o ao agente
	getAgente()->setRot(rot);
}