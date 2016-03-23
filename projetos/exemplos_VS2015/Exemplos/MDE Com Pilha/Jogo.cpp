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

	//	1) Inicializar a maquina de estados com o estado inicial
	//		Neste caso, cada estado � uma tela do jogo.
	//		Veja os arquivos .h e .cpp de cada tela para entender 
	//		o comportamento delas. Come�e pela classe base "Tela".
	maquina.inicializar(new TelaInicial);
}

void Jogo::finalizar()
{
	//	4)	Finalizar a maquina de estados
	maquina.finalizar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	2) Atualiza a maquina de estados
		maquina.atualizar();

		//	3) Se a maquina de estados ficou sem estados,
		//		 est� na hora de encerrar a aplicacao.
		//		 Ent�o marca a boolena gEvento.sair para true.
		//		 Isso vai encerrar o while.
		//	(IMPORTANTE) Apenas neste caso em que a maquina de estados representa as telas do jogo.
		//	Quando as telas acabam, o jogo encerra.	Em outros casos, isso pode n�o ser necess�rio.
		if (!maquina.temEstados())
			gEventos.sair = true;

		uniTerminarFrame();
	}
}