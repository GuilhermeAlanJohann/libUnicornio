#include "Janela.h"
#include "libUnicornio.h"

bool Janela::criada = false;

Janela::Janela()
{
	moveu_ = false;
	mudou_tamanho = false;
	minimizou_ = false;
	maximizou_ = false;
	restaurou_ = false;
	mouse_entrou = false;
	mouse_saiu = false;
	ganhou_foco = false;
	perdeu_foco = false;
	clicou_fechar = false;
	mouse_esta_dentro = false;
	esta_em_foco = false;

	x = 0;
	y = 0;
	largura_tela = 0;
	altura_tela = 0;
	largura = 0;
	altura = 0;
	id = -1;

	sdl_window = NULL;
	sdl_renderer = NULL;
	cor.r = 0;
	cor.g = 0;
	cor.b = 0;
	cor.a = 255;
}

Janela::~Janela()
{
}

bool Janela::criar(int largura_tela, int altura_tela, bool tela_cheia, string titulo_janela)
{
	if(criada)
	{
		uniErro("Impossivel criar janela. Uma janela ja existe!");
		return false;
	}

	limparEventos();
	mouse_esta_dentro = false;
	esta_em_foco = false;

	#if UNI_PLATAFORMA_MOVEL
		tela_cheia = true;
	#endif

	//	inicializa video
	if(tela_cheia)
		sdl_window = SDL_CreateWindow(titulo_janela.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		sdl_window = SDL_CreateWindow(titulo_janela.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largura_tela, altura_tela, SDL_WINDOW_SHOWN);

	if(sdl_window == NULL)
	{
        //	ERRO
        return false;
    }

	id = SDL_GetWindowID(sdl_window);

	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE /*| SDL_RENDERER_PRESENTVSYNC*/);

	if(sdl_renderer == NULL)
	{
        //	ERRO
        return false;
    }

	cor.r = 0;
	cor.g = 0;
	cor.b = 0;
	cor.a = 255;

	SDL_SetRenderDrawColor(sdl_renderer, cor.r, cor.g, cor.b, cor.a);
	SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");  // nao usa nenhum tipo de interpolacao para fazer a escala
	SDL_RenderSetLogicalSize(sdl_renderer, largura_tela, altura_tela);

	SDL_RenderClear(sdl_renderer);
	SDL_RenderPresent(sdl_renderer);

	this->largura_tela = largura_tela;
	this->altura_tela = altura_tela;

	SDL_GetWindowSize(sdl_window, &largura, &altura);
	SDL_GetWindowPosition(sdl_window, &x, &y);

	criada = true;
	return criada;
}

bool Janela::destruir()
{
	if(!criada)
	{
		return false;
	}

	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(sdl_window);

	criada = false;
	return criada;
}

void Janela::limparEventos()
{
	moveu_ = false;
	mudou_tamanho = false;
	minimizou_ = false;
	maximizou_ = false;
	restaurou_ = false;
	mouse_entrou = false;
	mouse_saiu = false;
	ganhou_foco = false;
	perdeu_foco = false;
	clicou_fechar = false;
}

void Janela::processarEvento(const SDL_Event& evento)
{
	if(evento.type == SDL_WINDOWEVENT && evento.window.windowID == id)
	{
		switch(evento.window.event)
		{
		case SDL_WINDOWEVENT_SHOWN:
			//	faz nada;
			break;

		case SDL_WINDOWEVENT_HIDDEN:
			//	faz nada;
			break;

		case SDL_WINDOWEVENT_RESIZED:
			//	faz nada. Estou usando SDL_WINDOWEVENT_SIZE_CHANGED para isso.
			break;

        case SDL_WINDOWEVENT_MOVED:
			moveu_ = true;
			x = evento.window.data1;
			y = evento.window.data2;
            break;

		case SDL_WINDOWEVENT_SIZE_CHANGED:
			mudou_tamanho = true;
			largura = evento.window.data1;
			altura = evento.window.data2;
            break;

        case SDL_WINDOWEVENT_MINIMIZED:
			minimizou_ = true;
            break;

        case SDL_WINDOWEVENT_MAXIMIZED:
            maximizou_ = true;
            break;

        case SDL_WINDOWEVENT_RESTORED:
			restaurou_ = true;
            break;

        case SDL_WINDOWEVENT_ENTER:
			mouse_entrou = true;
			mouse_esta_dentro = true;
            break;

        case SDL_WINDOWEVENT_LEAVE:
			mouse_saiu = true;
			mouse_esta_dentro = false;
            break;

        case SDL_WINDOWEVENT_FOCUS_GAINED:
			ganhou_foco = true;
			esta_em_foco = true;
            break;

        case SDL_WINDOWEVENT_FOCUS_LOST:
			perdeu_foco = true;
			esta_em_foco = false;
            break;

        case SDL_WINDOWEVENT_CLOSE:
			clicou_fechar = true;
            break;
		}
	}
}

bool Janela::moveu()
{
	return moveu_;
}

bool Janela::mudouTamanho()
{
	return mudou_tamanho;
}

bool Janela::minimizou()
{
	return minimizou_;
}

bool Janela::maximizou()
{
	return maximizou_;
}

bool Janela::restaurou()
{
	return restaurou_;
}

bool Janela::mouseEntrou()
{
	return mouse_entrou;
}

bool Janela::mouseEstaDentro()
{
	return mouse_esta_dentro;
}

bool Janela::mouseSaiu()
{
	return mouse_saiu;
}

bool Janela::ganhouFoco()
{
	return ganhou_foco;
}

bool Janela::estaEmFoco()
{
	return esta_em_foco;
}

bool Janela::perdeuFoco()
{
	return perdeu_foco;
}

bool Janela::clicouFechar()
{
	return clicou_fechar;
}

int Janela::getID()
{
	return id;
}

string Janela::getTitulo()
{
	return SDL_GetWindowTitle(sdl_window);
}

int Janela::getX()
{
	return x;
}

int Janela::getY()
{
	return y;
}

int Janela::getLargura()
{
	return largura;
}

int Janela::getAltura()
{
	return altura;
}

int Janela::getLarguraTela()
{
	return largura_tela;
}

int Janela::getAlturaTela()
{
	return altura_tela;
}

void Janela::obterPos(int &x, int &y)
{
	x = this->x;
	y = this->y;
}

void Janela::obterTamanho(int &larg, int &alt)
{
	larg = largura;
	alt = altura;
}

void Janela::obterTamanhoTela(int &larg, int &alt)
{
	larg = largura_tela;
	alt = altura_tela;
}

void Janela::obterCorDeFundo(int &vermelho, int &verde, int &azul)
{
	vermelho = cor.r;
	verde = cor.g;
	azul = cor.b;
}

bool Janela::estaEmModoPaisagem()
{
	return (altura < largura);
}

bool Janela::estaEmModoRetrato()
{
	return (largura < altura);
}

bool Janela::telaEstaEmModoPaisagem()
{
	return (altura_tela < largura_tela);
}

bool Janela::telaEstaEmModoRetrato()
{
	return (largura_tela < altura_tela);
}

bool Janela::estaEmTelaCheia()
{
	Uint32 flags = SDL_GetWindowFlags(sdl_window); 
	return (flags & SDL_WINDOW_FULLSCREEN_DESKTOP || flags & SDL_WINDOW_FULLSCREEN);
}

bool Janela::setIcone(string caminho_arquivo)
{
	SDL_Surface *surface = IMG_Load(caminho_arquivo.c_str());
	if(surface)
	{
		SDL_SetWindowIcon(sdl_window, surface);
		SDL_FreeSurface(surface);
		return true;
	}
	return false;
}

void Janela::setTitulo(string titulo)
{
	SDL_SetWindowTitle(sdl_window, titulo.c_str());
}

void Janela::setPos(int x, int y)
{
	this->x = x;
	this->y = y;

	SDL_SetWindowPosition(sdl_window, x, y);
}

void Janela::setTamanho(int larg, int alt)
{
	SDL_SetWindowSize(sdl_window, larg, alt);
	largura_tela = larg;
	altura_tela = alt;
}

void Janela::setTamanhoTela(int larg, int alt)
{
	SDL_RenderSetLogicalSize(sdl_renderer, larg, alt);
	largura_tela = larg;
	altura_tela = alt;
}

void Janela::setCorDeFundo(int vermelhor, int verde, int azul)
{
	cor.r = vermelhor;
	cor.g = verde;
	cor.b = azul;
}

void Janela::setTelaCheia(bool tela_cheia)
{
	if(tela_cheia)
		SDL_SetWindowFullscreen(sdl_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		SDL_SetWindowFullscreen(sdl_window, 0);

	SDL_RenderSetLogicalSize(sdl_renderer, largura_tela, altura_tela);
}

void Janela::ajustarTela()
{
	int l, a;
	if(estaEmModoPaisagem())
	{
		l = max(largura_tela, altura_tela);
		a = min(largura_tela, altura_tela);
	}
	else
	{
		l = min(largura_tela, altura_tela);
		a = max(largura_tela, altura_tela);
	}
	SDL_RenderSetLogicalSize(sdl_renderer, l, a);
	largura_tela = l;
	altura_tela = a;
}

void Janela::limpar()
{
	SDL_SetRenderDrawColor(sdl_renderer, cor.r, cor.g, cor.b, cor.a);
	SDL_RenderClear(sdl_renderer);
}

void Janela::desenhar()
{
	SDL_RenderPresent(sdl_renderer);
}