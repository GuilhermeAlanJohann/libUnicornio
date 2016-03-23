#include "EstadoGirando.h"
#include "EstadoMovendo.h"


EstadoGirando::EstadoGirando(Vetor2D p)
{
	//	Pega a posição destino do agente,
	//		para saber para onde ele deve girar.
	destino = p;
}

EstadoGirando::~EstadoGirando()
{
}

void EstadoGirando::entrar()
{
	//	2.1) Ao entrar no estado, ajusta a animação
	getSprite()->setSpriteSheet("movendo");
	getSprite()->setVelocidadeAnimacao(10.0f);
}

void EstadoGirando::sair()
{
	//	2.3) Ao sair do estado, não precisamos fazer nada
}

void EstadoGirando::atualizar(float dt)
{
	//	2.2) Durante a atualização...

	//	Avançar a animação
	getSprite()->avancarAnimacao(dt);

	//	Se pressiou o botão esquerdo do mouse,
	if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
	{
		//	Muda o destino.
		destino.set(gMouse.x, gMouse.y);
	}

	float rot = getAgente()->getRot();
	float vel = 90.0f;	//	velocidade de rotação

	//	Direção do agente
	Vetor2D dir(1, 0);
	dir.rotacionar(rot);

	//	Direção que o agente deve ir
	Vetor2D dirDestino = destino - getAgente()->getPos();
	float rotDestino = dirDestino.getAngulo();

	//	Angulo entre o vetor de direção e o vetor de direção destino
	float ang = dir.getAnguloAteVetor(dirDestino);

	//	Se a rotação está muito próxima,
	if (fabsf(ang) < vel*dt)
	{
		//	força a rotação para o destino
		rot = rotDestino;
		//	Terminou a rotação
		//	Muda o estado (EstadoMovendo)
		getAgente()->trocarEstado(new EstadoMovendo(destino));
	}
	else	//	Se não, aplica a rotação segundo a velocidade
	{
		float sinal = 1.0f;	// sinal da rotação (-1 ou +1);
		if (ang < 0)
			sinal = -1.0f;

		//	Multiplica a velocidade de rotação pelo tempo,
		//	para saber a velocidade em um frame.
		//	Multiplica pelo sinal para saber qual o lado da rotação
		//	Soma isso a rotação
		rot += vel*dt*sinal;
	}

	//	Aplica a nova rotação ao agente
	getAgente()->setRot(rot);
}