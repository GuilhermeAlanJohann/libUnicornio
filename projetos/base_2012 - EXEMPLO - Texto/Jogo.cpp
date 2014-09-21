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
	recursos.carregarFonte("fonte menor", "dados/fontes/morohashi.ttf", 32);
	recursos.carregarFonte("fonte maior", "dados/fontes/morohashi.ttf", 128);

	//	2)	Setar as fontes e os textos
	texto.setFonte("fonte menor");
	texto.setTexto("Exemplo");
	textoMaior.setFonte("fonte maior");
	textoMaior.setTexto("Exemplo");

	//	(Opcional) Setar cor para os textos. O padrão é branco.
	texto.setCor(0, 255, 0);
	textoMaior.setCor(255, 0, 0);

	//	(Opcional) Setar borda e cor da borda. O padrão é preto
	texto.setTamanhoBorda(1);
	texto.setCorBorda(255, 255, 255);
	textoMaior.setTamanhoBorda(2);
	textoMaior.setCorBorda(255, 255, 255);
}

void Jogo::finalizar()
{
	//	4)	(IMPORTANTE) Limpar o texto. Isto destroi a "imagem" associada ao texto e libera memoria, evitando possiveis crashs na finalizacao.
	texto.apagar();
	textoMaior.apagar();

	//	5) Descarregar tudo
	recursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	3)	Desenhar os textos (x, y, rot)
		textoMaior.desenhar(res_x/2, res_y/2);		//	bem no meio da tela
		texto.desenhar(res_x/2, res_y/2 + 64, 180);	//	um pouco mais para baixo e com rot 180 graus

		uniTerminarFrame();
	}
}