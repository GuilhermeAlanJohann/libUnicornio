#include "Jogo.h"
#include <random>

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(800, 600, false);

	//	vector que descreve a topologia da rede neural
	//		Neste caso, queremos uma rede com:
	//		2 Neur�nios na camada de entrada
	//		3 Neur�nios na camada oculta (uma camada oculta apenas para esse exemplo)
	//		1 Neur�nio  na camada de saida
	vector<unsigned int> topologia;
	topologia.push_back(2);		//	camada de entrada
	topologia.push_back(3);		//	camada oculta
	topologia.push_back(1);		//	camada de saida

	//	1) Inicializar a rede passando a topologia como par�metro
	rede.inicializar(topologia);
	
	//	(Opcional) Setar os par�metros da rede.
	rede.setTaxaDeAprendizado(0.15);	//	Taxa de aprendizado. O padr�o � 0.2.

	treinando = false;
	gDebug.setPos(50, 150);
}

void Jogo::finalizar()
{
	//	5)	Finalizar a rede
	rede.finalizar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.pressionou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		gDebug.depurar("treinando", treinando);

		atualizarInput();
		atualizar();

		desenharInstrucoes();
		
		uniTerminarFrame();
	}
}

void Jogo::atualizarInput()
{
	if (gTeclado.pressionou[TECLA_ENTER])
	{
		treinando = !treinando;
	}

	if (gTeclado.pressionou[TECLA_S])
	{
		//	3) Quando a rede j� est� treinada, podemos salvar os pesos dela para 
		//		poder recarregar mais tarde. Assim, n�o precisamos treinar a rede 
		//		toda vez que o jogo inicia.
		if(UNI_PLATAFORMA_MOVEL)
			rede.salvarPesos(uniGetCaminhoPreferencias() + "rede neural.pesos_xor.txt");
		else
			rede.salvarPesos("assets/rede neural/pesos_xor.txt");
	}

	if (gTeclado.pressionou[TECLA_C])
	{
		//	4) Quando a rede j� foi treinada anteriormente, podemos carregar os pesos salvos. 
		//		Assim, n�o precisamos treinar a rede novamente.
		if(UNI_PLATAFORMA_MOVEL)
			rede.carregarPesos(uniGetCaminhoPreferencias() + "rede neural.pesos_xor.txt");
		else
			rede.carregarPesos("assets/rede neural/pesos_xor.txt");
	}
}

void Jogo::atualizar()
{
	//	2) Atualiza a rede
	//		O processo de atualiza��o de uma rede funciona em 
	//		2 etapas quando a rede j� est� treinada e 
	//		3 etapas quando ela ainda est� sendo treinada.
	//
	//		S�o elas:
	//	2.1) Alimentar a rede com os par�metros de entrada.
	//			O n�mero de parametros varia conforme a topologia da rede.
	//			Neste caso, temos uma rede com 2 nur�nios na camada de entrada,
	//			portanto precisamos de 2 par�metros de entrada.
	//			Para isso usa-se o m�todo "alimentar".
	//	2.2) Pegar os resultados da rede.
	//			Ap�s alimentada, a rede gerou resultados/sa�das.
	//			O n�mero de sa�das tamb�m varia conforme a topologia da rede.
	//			Neste caso, temos uma rede com 1 neur�nio de sa�da, 
	//			portanto teremos apenas 1 sa�da.
	//	2.3) Retropropagar (treinar)
	//			Essa etapa � necess�ria apenas quando a rede est� sendo treinada.
	//			� nessa etapa que os pesos da rede ser�o ajustados conforme os
	//			resultados desejados. Para isso usa-se o m�todo "retropropagar"
	//			passando como par�metro os resultados desejados.
	//			Neste caso, temos uma rede com 1 neur�nio de sa�da, 
	//			portanto passamos apenas 1 sa�da desejada.

	vector<double> entradas;
	vector<double> saidas;
	vector<double> saidasDesejadas;
	entradas.resize(2);
	saidasDesejadas.resize(1);
	
	//	XOR [0, 0] = 0;
	entradas[0] = 0;
	entradas[1] = 0;
	rede.alimentar(entradas);					//	Alimentar
	saidas = rede.getResultados();				//	Resultados
	gDebug.depurar("[0, 0] = 0", saidas[0]);
	saidasDesejadas[0] = 0;
	if (treinando)
		rede.retropropagar(saidasDesejadas);	//	Retropropagar

	//	XOR [0, 1] = 1;
	entradas[0] = 0;
	entradas[1] = 1;
	rede.alimentar(entradas);					//	Alimentar				
	saidas = rede.getResultados();				//	Resultados
	gDebug.depurar("[0, 1] = 1", saidas[0]);
	saidasDesejadas[0] = 1;
	if (treinando)
		rede.retropropagar(saidasDesejadas);	//	Retropropagar
	
	//	XOR [1, 0] = 1;
	entradas[0] = 1;
	entradas[1] = 0;
	rede.alimentar(entradas);					//	Alimentar
	saidas = rede.getResultados();				//	Resultados
	gDebug.depurar("[1, 0] = 1", saidas[0]);
	saidasDesejadas[0] = 1;
	if (treinando)
		rede.retropropagar(saidasDesejadas);	//	Retropropagar
	
	//	XOR [1, 1] = 0;
	entradas[0] = 1;
	entradas[1] = 1;
	rede.alimentar(entradas);					//	Alimentar
	saidas = rede.getResultados();				//	Resultados
	gDebug.depurar("[1, 1] = 0", saidas[0]);
	saidasDesejadas[0] = 0;
	if (treinando)
		rede.retropropagar(saidasDesejadas);	//	Retropropagar

}

void Jogo::desenharInstrucoes()
{
	string txt = "Instru��es:\n"
		"Pressione [ENTER] para come�ar/parar/continuar treinamento\n"
		"Pressione [S] pra salvar os pesos da rede\n"
		"Pressione [C] pra carregar os pesos da rede";

	gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
}