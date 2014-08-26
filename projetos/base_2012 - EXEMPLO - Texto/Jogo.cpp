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
	fonte.carregar("dados/fontes/morohashi.ttf", 32);
	fonteMaior.carregar("dados/fontes/morohashi.ttf", 128);

	//	2)	Setar as fontes e os textos
	texto.setFonte(&fonte);
	texto.setTexto("Exemplo");
	textoMaior.setFonte(&fonteMaior);
	textoMaior.setTexto("Exemplo");

	//	3)	(Opcional) Setar cor para os textos. O padrão é branco.
	texto.setCor(0, 255, 0);
	textoMaior.setCor(255, 0, 0);
}

void Jogo::finalizar()
{
	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	4)	Desenhar os textos (x, y, rot)
		textoMaior.desenhar(res_x/2, res_y/2);		//	bem no meio da tela
		texto.desenhar(res_x/2, res_y/2 + 64, 180);	//	um pouco mais para baixo e com rot 180 graus

		uniTerminarFrame();
	}
}