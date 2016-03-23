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

		//	depois testa as colis�es
		testarColisoes();

		//	por �ltimo, desenha tudo
		tiro.desenhar();
		nave.desenhar();
		desenharInstru��es();

		uniTerminarFrame();
	}
}

void Jogo::inicializarNave()
{
	//	calcula posi��o
	int x, y;
	x = gJanela.getLargura() / 2;
	y = gJanela.getAltura() - 60;

	//	Seta spritesheet e posi��o
	nave.setSpriteSheet("nave");
	nave.setPos(x, y);

	//	Aumenta a escala s� pra ficar maior
	nave.setEscala(2.5, 2.5);
}

void Jogo::inicializarTiro()
{
	//	calcula posi��o
	int x, y;
	x = gJanela.getLargura() / 2;
	y = -40;

	//	Seta spritesheet e posi��o
	tiro.setSpriteSheet("tiro");
	tiro.setPos(x, y);

	//	Aumenta a escala s� pra ficar maior
	tiro.setEscala(2.5, 2.5);
}

void Jogo::testarColisoes()
{
	//	1) Testar e responder as colis�es.

	//	Colisao de tiro com nave
	//		Para este exemplo usamos os sprites do Tiro e da Nave como colisores, ou seja,
	//		o retangulo formado pelo sprite ser� a �rea de colisao do objeto.
	//		Para testar a colis�o entre dois sprites usa-se o m�todo "uniTestarColisao" ou
	//		"uniTestarColisaoSpriteComSprite" passando como par�metro:
	//		o Sprite, a posi��o (x, y) e a rota��o do 1� objeto, seguido de
	//		o Sprite, a posi��o (x, y) e a rota��o do 2� objeto.
	//		Caso exista colis�o, a fun��o retornar� true, caso n�o exista, retornar� false;
	if(uniTestarColisao(tiro.getSprite(), tiro.getPosX(), tiro.getPosY(), tiro.getRot(),
						nave.getSprite(), nave.getPosX(), nave.getPosY(), nave.getRot()))
	{
		tiro.setPos(tiro.getPosX(), -40);
	}


	//	Colisao de mouse com tiro
	//		Para este exemplo usamos os Sprite do Tiro e a posi��o do mouse como colisores, ou seja,
	//		o retangulo formado pelo sprite ser� a �rea de colisao do objeto, que ir� colidir se a posi��o
	//		do mouse estiver dentro do retangulo.
	//		Para testar a colis�o entre um ponto e um sprite usa-se o m�todo "uniTestarColisao" ou
	//		"uniTestarColisaoPontoComSprite" passando como par�metro:
	//		a posi��o (x, y) do ponto, seguido de
	//		o Sprite, a posi��o (x, y) e a rota��o do objeto.
	//		Caso exista colis�o, a fun��o retornar� true, caso n�o exista, retornar� false;
	if(uniTestarColisao(gMouse.x, gMouse.y, tiro.getSprite(), tiro.getPosX(), tiro.getPosY(), tiro.getRot()))
	{
		tiro.setPos(tiro.getPosX(), -40);
	}

	//	(OBS) Outras fun��es de colis�o tamb�m existem.
	//		� possivel testar coli�es entre diferentes formas geom�tricas e sprites.
	//		Sprites s�o sempre tratados como se fossem ret�ngulos.
	//		As formas "colidiveis" s�o as seguintes: (da mais simples para a mais complexa)
	//			Ponto
	//			Linha
	//			C�rculo
	//			Ret�ngulo
	//			Pol�gono
	//			Sprite (Ret�ngulo)
	//		Para testar a colis�o entre uma forma e outra usa-se uma fun��o com a segunte
	//		nomenclatura:
	//		uniTestarColis�o + <NomeDaFormaMaisSimples> + "Com" + <NomeDaFormaMaisComplexa>
	//		Ex: 
	//			"uniTestarColisaoCirculoComRetangulo"
	//			"uniTestarColisaoPoligonoComSprite"
	//			"uniTestarColisaoPontoComCirculo"
	//			"uniTestarColisaoLinhaComLinha"
}

void Jogo::desenharInstru��es()
{
	string txt = "Instru��es:\n"
		"    As colis�es acontecem quando o m�ssel atinge a nave, ou quando o mouse\n"
		"    passa cima do m�ssel.\n"
		"    Espere o m�ssel atingir a nave para ver ele retornar a posi��o original.\n"
		"    Passe o mouse em cima do m�ssel para ver ele rotornar a posi��o original tamb�m.";

	gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
}