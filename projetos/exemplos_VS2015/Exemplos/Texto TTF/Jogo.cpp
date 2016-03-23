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

	//	1)	Carregar a fonte (passando o tamanho da fonte como parametro)
	gRecursos.carregarFonte("fonte1", "assets/texto/arial.ttf", 32);

	//	2)	Setar a fonte e a string do texto
	texto.setFonte("fonte1");
	texto.setString("A libUnic�rnio � D+\nEla tem textos coloridos e com quebra de linha!");

	//	(Opcional)	Formatar o texto
	//		Para a formata��o funcionar corretamente, ela deve ser feita, 
	//		preferencialmente, ap�s setar a fonte e a string
	texto.setCor(230, 230, 230);				//	Muda a cor do texto. O padr�o � branco.
	texto.setAlinhamento(TEXTO_CENTRALIZADO);	//	Alinhamento do texto. O Padr�o � TEXTO_ALINHADO_A_ESQUERDA.
	texto.setEspacamentoLinhas(1.5f);			//	Espa�amento entre as linhas. O padr�o � 1.0f.
	texto.setLarguraMaxima(300);				//	Largura m�xima do texto. Se ultrapassada o texto quebra para outra linha
												//	se igual a 0, a largura � infinita.

	texto.setCorPalavra("libUnic�rnio", 2, 163, 233);	//	Setar a cor de uma palavra (ou trecho da string)
	texto.setCorPalavra("coloridos", 237, 28, 36);		//	Setar a cor de uma palavra (ou trecho da string)

}

void Jogo::finalizar()
{
	//	4) Descarregar tudo
	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	3)	Desenhar o texto (x, y, rot)
		texto.desenhar(gJanela.getLargura()/2, gJanela.getAltura()/2);		//	bem no meio da tela

		uniTerminarFrame();
	}
}