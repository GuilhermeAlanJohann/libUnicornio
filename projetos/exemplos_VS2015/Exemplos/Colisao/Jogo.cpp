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

	//	carregar os spritesheets
	gRecursos.carregarSpriteSheet("nave", "assets/colisao/nave.png", 1, 1);
	gRecursos.carregarSpriteSheet("tiro", "assets/colisao/tiro.png", 1, 2);

	//	inicializar os objetos
	inicializarNave();
	inicializarTiro();
}

void Jogo::finalizar()
{
	//	descarregar os spritesheets
	gRecursos.descarregarTodosSpriteSheets();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	primeiro atualiza
		tiro.atualizar();

		//	depois testa as colisões
		testarColisoes();

		//	por último, desenha tudo
		tiro.desenhar();
		nave.desenhar();
		desenharInstruções();

		uniTerminarFrame();
	}
}

void Jogo::inicializarNave()
{
	//	calcula posição
	int x, y;
	x = gJanela.getLargura() / 2;
	y = gJanela.getAltura() - 60;

	//	Seta spritesheet e posição
	nave.setSpriteSheet("nave");
	nave.setPos(x, y);

	//	Aumenta a escala só pra ficar maior
	nave.setEscala(2.5, 2.5);
}

void Jogo::inicializarTiro()
{
	//	calcula posição
	int x, y;
	x = gJanela.getLargura() / 2;
	y = -40;

	//	Seta spritesheet e posição
	tiro.setSpriteSheet("tiro");
	tiro.setPos(x, y);

	//	Aumenta a escala só pra ficar maior
	tiro.setEscala(2.5, 2.5);
}

void Jogo::testarColisoes()
{
	//	1) Testar e responder as colisões.

	//	Colisao de tiro com nave
	//		Para este exemplo usamos os sprites do Tiro e da Nave como colisores, ou seja,
	//		o retangulo formado pelo sprite será a área de colisao do objeto.
	//		Para testar a colisão entre dois sprites usa-se o método "uniTestarColisao" ou
	//		"uniTestarColisaoSpriteComSprite" passando como parâmetro:
	//		o Sprite, a posição (x, y) e a rotação do 1º objeto, seguido de
	//		o Sprite, a posição (x, y) e a rotação do 2º objeto.
	//		Caso exista colisão, a função retornará true, caso não exista, retornará false;
	if(uniTestarColisao(tiro.getSprite(), tiro.getPosX(), tiro.getPosY(), tiro.getRot(),
						nave.getSprite(), nave.getPosX(), nave.getPosY(), nave.getRot()))
	{
		tiro.setPos(tiro.getPosX(), -40);
	}


	//	Colisao de mouse com tiro
	//		Para este exemplo usamos os Sprite do Tiro e a posição do mouse como colisores, ou seja,
	//		o retangulo formado pelo sprite será a área de colisao do objeto, que irá colidir se a posição
	//		do mouse estiver dentro do retangulo.
	//		Para testar a colisão entre um ponto e um sprite usa-se o método "uniTestarColisao" ou
	//		"uniTestarColisaoPontoComSprite" passando como parâmetro:
	//		a posição (x, y) do ponto, seguido de
	//		o Sprite, a posição (x, y) e a rotação do objeto.
	//		Caso exista colisão, a função retornará true, caso não exista, retornará false;
	if(uniTestarColisao(gMouse.x, gMouse.y, tiro.getSprite(), tiro.getPosX(), tiro.getPosY(), tiro.getRot()))
	{
		tiro.setPos(tiro.getPosX(), -40);
	}

	//	(OBS) Outras funções de colisão também existem.
	//		É possivel testar coliões entre diferentes formas geométricas e sprites.
	//		Sprites são sempre tratados como se fossem retângulos.
	//		As formas "colidiveis" são as seguintes: (da mais simples para a mais complexa)
	//			Ponto
	//			Linha
	//			Círculo
	//			Retângulo
	//			Polígono
	//			Sprite (Retângulo)
	//		Para testar a colisão entre uma forma e outra usa-se uma função com a segunte
	//		nomenclatura:
	//		uniTestarColisão + <NomeDaFormaMaisSimples> + "Com" + <NomeDaFormaMaisComplexa>
	//		Ex: 
	//			"uniTestarColisaoCirculoComRetangulo"
	//			"uniTestarColisaoPoligonoComSprite"
	//			"uniTestarColisaoPontoComCirculo"
	//			"uniTestarColisaoLinhaComLinha"
}

void Jogo::desenharInstruções()
{
	string txt = "Instruções:\n"
		"    As colisões acontecem quando o míssel atinge a nave, ou quando o mouse\n"
		"    passa cima do míssel.\n"
		"    Espere o míssel atingir a nave para ver ele retornar a posição original.\n"
		"    Passe o mouse em cima do míssel para ver ele rotornar a posição original também.";

	gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
}