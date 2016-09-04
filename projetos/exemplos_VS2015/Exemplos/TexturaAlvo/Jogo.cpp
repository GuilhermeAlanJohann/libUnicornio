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

	//	O resto da inicializa��o vem aqui!
	//	...

	//	1)	Cria a textura alvo, passando o tamanho dela em pixels.
	//		TexturaAlvo � uma textura na qual se pode desenhar, como se fosse uma tela.
	//		Ao criar a textura alvo, ela � totalmente transparente.
	alvo.criar(400, 300);
}

void Jogo::finalizar()
{
	//	O resto da finaliza��o vem aqui (provavelmente, em ordem inversa a inicializa��o)!
	//	...

	//	7)	Destruir a textura alvo
	alvo.destruir();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	Seu c�digo vem aqui!
		//	...

		//	2)	Ativa a textura alvo.
		//		A partir deste momento, tudo que for desenhado (Sprite, Texto, Textura, TileMap, primitivas, etc.)
		//		ser� desenhado na textura alvo e n�o na tela.
		alvo.ativar();

		//	3)	Limpa a textura alvo (apaga tudo que foi desenhado nela)
		//		Opcionalmente, pode-se passar uma cor como par�metro
		alvo.limpar();

		//	4)	Desenha as coisas.
		//		Ex: Um retangulo branco do tamanho da textura para indicar a borda dela
		gGraficos.desenharRetangulo(Quad(0, 0, alvo.getLargura(), alvo.getAltura()), 255, 255, 255, 255);
		//		Ex: Um circulo azul preenchido de raio 30 na posi��o 100, 100.
		gGraficos.desenharCirculo(100, 100, 30, 0, 0, 255, 255, true);

		//	5)	Desativa a textura alvo.
		//		A partir deste momento, tudo que for desenhado ser� desenhado na tela, n�o mais na textura
		alvo.desativar();

		//	6)	Desenhar a textura alvo na tela.
		//		A textura alvo pode ser desenhada da mesma maneira que uma textura normal
		alvo.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

		uniTerminarFrame();
	}
}