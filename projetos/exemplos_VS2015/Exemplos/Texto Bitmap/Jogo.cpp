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

	//	string contendo os caracteres usados na imagem da fonte bitmap.
	//		Esses caracteres devem estar em ordem, para funcionar corretamente.
	//		Ex: Um 'B' nunca pode vir antes de um 'A', e assim por diante.
	string caracteres =
		" ! # %      ,   "
		"0123456789:;   ?"
		" ABCDEFGHIJKLMNO"
		"PQRSTUVWXYZ     "
		" abcdefghijklmno"
		"pqrstuvwxyz     ";

	//	1)	Carregar a fonte BMP passando como parâmetro os caracteres usados na imagem,
	//		o número de caracteres em x, e o número de caracteres em y.
	//		Opcionalmente pode-se passar também a qualidade de escala da imagem. O Padrão é QUALIDADE_ESCALA_BAIXA
	gRecursos.carregarFonte("fonteBMP", "assets/texto/F1fuv.png", caracteres, 16, 6, QUALIDADE_ESCALA_ALTA);

	//	(Opcional)	Alterar o avanço dos glifos (caracteres), para que eles não fiquem muito afastados entre si
	Fonte* fonte = gRecursos.getFonte("fonteBMP");
	for (int i = 0; i < fonte->getNumGlifos(); ++i)
		fonte->getGlifoPeloIndice(i)->avanco = 44;

	//	2)	Setar a fonte e a string no texto
	texto.setFonte("fonteBMP");
	texto.setString("A libUnicornio tem suporte a fontes bitmap!");

	//	(Opcional)	Formatar o texto
	//		Para a formatação funcionar corretamente, ela deve ser feita, 
	//		preferencialmente, após setar a fonte e a string
	texto.setAlinhamento(TEXTO_CENTRALIZADO);	//	Alinhamento do texto. O Padrão é TEXTO_ALINHADO_A_ESQUERDA.
	texto.setLarguraMaxima(550);				//	Largura máxima do texto. Se ultrapassada o texto quebra para outra linha
												//	se igual a 0, a largura é infinita.
}

void Jogo::finalizar()
{
	//	4)	Descarregar a fonte
	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	3)	Desenhar o texto (x, y, rot)
		texto.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);		//	bem no meio da tela

		uniTerminarFrame();
	}
}