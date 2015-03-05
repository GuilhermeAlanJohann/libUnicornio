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

	//	1)	Carregar as fontes (passando o tamanho da fonte como parametro)
	recursos.carregarFonte("fonte1", "dados/fontes/morohashi.ttf", 32);

	//	2)	Setar a fonte e a string do texto
	texto.setFonte("fonte1");
	texto.setString("Este eh\num texto de\nexemplo!");

	//	(Opcional) Setar cor para os textos. O padrão é branco.
	texto.setCor(0, 255, 0);

	//	(Opcional) Setar alinhamento. O padrão é alinhado à esquerda.
	texto.setAlinhamento(TEXTO_CENTRALIZADO);

	//	(Opcional) Setar espaçamento das linhas. O padrão é 1.0f.
	texto.setEspacamentoLinhas(1.5f);
}

void Jogo::finalizar()
{
	//	4) Descarregar tudo
	recursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	3)	Desenhar o texto (x, y, rot)
		texto.desenhar(janela.getLarguraTela()/2, janela.getAlturaTela()/2);		//	bem no meio da tela

		uniTerminarFrame();
	}
}