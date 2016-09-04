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

	//	Carrega spritesheet para o fundo
	gRecursos.carregarSpriteSheet("fundo", "assets/comum/fundo.png");

	sprFundo.setSpriteSheet("fundo");
	gJanela.setCorDeFundo(30, 210, 230);

	//	Seta a posi��o do painel de debug
	gDebug.setPos(150, 350);
}

void Jogo::finalizar()
{
	//	Descarrega spritesheet do fundo
	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	Se pressionou R, restaura o painel de debug
		if (gTeclado.pressionou[TECLA_R])
			gDebug.restaurar();


		//	Depurar variaveis
		gDebug.depurar("FPS", (int)gTempo.getFPS());
		gDebug.depurar("deltaTempo", gTempo.getDeltaTempo());
		gDebug.depurar("mouse", Vetor2D(gMouse.x, gMouse.y));
		gDebug.depurar("retanguloTela", Quad(0, 0, gJanela.getLargura(), gJanela.getAltura()));

		//	Cria um erro
		gDebug.erro("Erro Teste", this);

		//	Opcionalmente, passa-se uma cor para a depura��o
		gDebug.depurar("Verde", "Este � um texto Verde", Cor(0, 255, 0));


		//	Desenhar fundo, para poder ver melhor a transpar�ncia do painel
		sprFundo.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
		desenharInstrucoes();

		uniTerminarFrame();
	}
}

void Jogo::desenharInstrucoes()
{
	string txt = "Instru��es:\n"
		"    O Painel de Debug (gDebug) serve para depurar vari�veis\n"
		"    e criar erros em tempo real.\n"
		"    Ele pode depurar v�rios tipos de dados, inclusive Vetor2D e Retangulo.\n"
		"    -> Use os m�todos 'depurar' e 'erro' para fazer isso.\n"
		"    Al�m disso, � possivel trocar a cor do painel e dos textos.\n"
		"    Tamb�m � possivel mover o painel por c�digo ou usando o mouse.\n"
		"    E ele possui bot�es!\n"
		"    Al�m de tudo, ele n�o muda sua resolu��o conforme o tamanho da tela, portanto\n"
		"    ele permanece o tempo todo legivel. Experimente mudar o tamanho da tela em tela cheia.\n"
		"    \n"
		"    Clique na barra de t�tulo do painel e arraste para move-lo.\n"
		"    Clique no bot�o [_] para minimizar o painel.\n"
		"    Clique no bot�o [X] para fechar o painel\n"
		"    Pressione [R] para restaurar o painel.";

	gGraficos.desenharTexto(txt, 25, 25, 0, 0, 0, 255, 0, 0);
}