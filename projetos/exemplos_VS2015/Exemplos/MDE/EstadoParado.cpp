#include "EstadoParado.h"



EstadoParado::EstadoParado()
{
}

EstadoParado::~EstadoParado()
{
}

void EstadoParado::entrar()
{
	//	2.1) Ao entrar no estado, ajusta a animação
	getSprite()->setSpriteSheet("parado");
	getSprite()->setVelocidadeAnimacao(10.0f);
}

void EstadoParado::sair()
{
	//	2.3) Ao sair do estado, não precisamos fazer nada
}

void EstadoParado::atualizar(float dt)
{
	//	2.2) Durante a atualização...

	//	Avançar a animação
	getSprite()->avancarAnimacao(dt);

	//	Se pressiou o botão esquerdo do mouse,
	if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
	{
		//	Muda para o estado "Girando"
		//		Neste caso, estamos passando o posição do mouse como 
		//		parâmetro para o contrutor do estado, pois queremos que
		//		o agente gire para essa posição durante o estado girando.
		Vetor2D pos(gMouse.x, gMouse.y);
		getAgente()->trocarEstado(new EstadoGirando(pos));
	}
}