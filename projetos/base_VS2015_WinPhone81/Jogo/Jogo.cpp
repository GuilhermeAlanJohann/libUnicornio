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

	gRecursos.carregarSpriteSheet("logo", "assets/logo.png");  
	gRecursos.carregarFonte("arial", "assets/arial.ttf", 32);
	//gRecursos.carregarFonte("arial", "assets/fonte_padrao.ttf", 32);
	gRecursos.carregarAudio("som", "assets/shot.wav");
	gRecursos.carregarMusica("musica", "assets/Taylor Swift - Shake It Off.ogg");

	spr.setSpriteSheet("logo");
	txt.setFonte("arial");
	txt.setString("Teste!");
	som.setAudio("som");

	gMusica.tocar("musica", false);
}

void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!
	//	...

	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	Seu código vem aqui!
		//	...
		if (gTeclado.pressionou[TECLA_ENTER])
			som.tocar();

		spr.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
		txt.desenhar(gJanela.getLargura() / 2, gJanela.getAltura()*0.8);

		uniTerminarFrame();
	}
}