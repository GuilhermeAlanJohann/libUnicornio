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

	//	O resto da inicialização vem aqui!
	//	...

	//	1)	Cria a textura alvo, passando o tamanho dela em pixels.
	//		TexturaAlvo é uma textura na qual se pode desenhar, como se fosse uma tela.
	//		Ao criar a textura alvo, ela é totalmente transparente.
	alvo.criar(400, 300);
}

void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!
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

		//	Seu código vem aqui!
		//	...

		//	2)	Ativa a textura alvo.
		//		A partir deste momento, tudo que for desenhado (Sprite, Texto, Textura, TileMap, primitivas, etc.)
		//		será desenhado na textura alvo e não na tela.
		alvo.ativar();

		//	3)	Limpa a textura alvo (apaga tudo que foi desenhado nela)
		//		Opcionalmente, pode-se passar uma cor como parâmetro
		alvo.limpar();

		//	4)	Desenha as coisas.
		//		Ex: Um retangulo branco do tamanho da textura para indicar a borda dela
		gGraficos.desenharRetangulo(Quad(0, 0, alvo.getLargura(), alvo.getAltura()), 255, 255, 255, 255);
		//		Ex: Um circulo azul preenchido de raio 30 na posição 100, 100.
		gGraficos.desenharCirculo(100, 100, 30, 0, 0, 255, 255, true);

		//	5)	Desativa a textura alvo.
		//		A partir deste momento, tudo que for desenhado será desenhado na tela, não mais na textura
		alvo.desativar();

		//	6)	Desenhar a textura alvo na tela.
		//		A textura alvo pode ser desenhada da mesma maneira que uma textura normal
		alvo.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

		uniTerminarFrame();
	}
}