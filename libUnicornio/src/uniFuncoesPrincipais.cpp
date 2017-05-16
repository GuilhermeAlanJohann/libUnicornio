#include "uniFuncoesPrincipais.h"
#include "Global.h"

//
//	------- Variaveis Globais ------- //
//
bool uniInicializada = false;

//
//	-------- FUNCS EXTERNAS --------- //
//

bool uniInicializar(int largura_janela, int altura_janela, bool tela_cheia, string titulo_janela, int flags_sdl_window)
{
	if (uniEstaInicializada())
	{
		gDebug.erro("uniInicializar() falhou. A biblioteja já foi inicializada anteriormente.");
		return false;
	}

	//	inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	if (!SDL_WasInit(0))
		return false;

	//	inicializa SDL_ttf (biblioteca de fontes)
	TTF_Init();
	if (!TTF_WasInit())
	{
		SDL_Quit();
		return false;
	}

	//	inicializa globais
	Global::getInstancia().inicializar();

	//	cria janela principal
	bool janela_ok = gJanela.criar(largura_janela, altura_janela, tela_cheia, titulo_janela, flags_sdl_window);
	if (!janela_ok)
	{
		Global::getInstancia().finalizar();
		TTF_Quit();
		SDL_Quit();
		return false;
	}

	uniInicializada = true;		//	seta uniInicializada para true. Precisa ser feito aqui para poder carregar a fonte padrao
	gGraficos.inicializar(gJanela.getSDL_Renderer());
	if (!gGraficos.getFontePadrao())
	{
		//	se a fonte padrao nao foi carregada,
		//  limpa o painel de debug e desativa 
		//	para nao tentar desenhar sem ter uma fonte.
		gDebug.limpar();
		gDebug.desativar();
	}
	uniInicializada = false;	//	volta a ser false para continuar a inicializacao

								//	inicializa painel de debug
	gDebug.inicializar();

	//	inicializa audio
	gAudios.inicializar();
	if (!gAudios.estaInicializado())
	{
		//	Mostra mensagem de erro
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Erro ao inicializar modulo de audio!", 
			"Um erro ocorreu ao tentar inicializar o modulo de audio da libUnicornio:"
			" Certifique-se de que você possui seus drivers de audio atualizados e tente novamente.",
			gJanela.getSDL_Window());

		//	Finaliza tudo
		gDebug.finalizar();
		gGraficos.finalizar();
		gJanela.destruir();
		Global::getInstancia().finalizar();
		TTF_Quit();
		SDL_Quit();

		//	Força o fim da aplicação
		exit(EXIT_FAILURE);
		return false;
	}

	//	inicializa handlers de eventos
	gEventos.janela = &gJanela;
	gEventos.mouse = &gMouse;
	gEventos.teclado = &gTeclado;
	gEventos.joysticks = &gJoysticks;
	gEventos.toques = &gToques;
	gEventos.mixador = &gAudios;
	gEventos.atualizar();

	//	inicializa gerenciador de tempo
	gTempo.inicializar();

	//	seta uniInicializada para true
	uniInicializada = true;

	return true;
}

void uniFinalizar()
{
	if (!uniEstaInicializada())
		return;

	//	finaliza gerenciador de tempo
	gTempo.finalizar();

	//	finaliza gerenciador de recursos
	gRecursos.descarregarTudo();

	// finaliza audio
	gAudios.finalizar();

	//	finaliza painel de debug
	gDebug.finalizar();

	//	finaliza gerenciador de graficos
	gGraficos.finalizar();

	//	destroi janela principal
	gJanela.destruir();

	//	finaliza globais
	Global::getInstancia().finalizar();

	// finaliza SDL_ttf (biblioteca de fontes)
	TTF_Quit();

	//	finaliza SDL
	SDL_Quit();

	//	seta uniInicializada para false
	uniInicializada = false;
}

bool uniEstaInicializada()
{
	return uniInicializada;
}

void uniIniciarFrame(bool limitarFPS)
{
	if (!uniInicializada) return;

	gTempo.atualizar(limitarFPS);

	gEventos.atualizar();

	gJanela.fading.atualizar();
}

void uniTerminarFrame(bool limpar_janela)
{
	if (!uniInicializada)
		return;

	//	atualiza o painel debug logo antes de desenhar,
	//	isso é feito aqui, e não uniIniciarFrame() para evitar
	//	problema de 'one frame off' no tamanho do painel, o que pode
	//	causar o desenho incorreto dos textos do painel durante este frame
	gDebug.atualizar();
	gJanela.fading.desenhar();
	gDebug.desenhar();
	gJanela.desenhar();

	if (limpar_janela)
		gJanela.limpar();
}

void uniDormir(int milisec)
{
	SDL_Delay(milisec);
}

UniVersao uniGetVersao()
{
	UniVersao versao;
	versao.maior = 1;
	versao.menor = 1;
	versao.patch = 2;
	return versao;
}