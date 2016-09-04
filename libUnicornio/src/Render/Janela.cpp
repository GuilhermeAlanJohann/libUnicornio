#include "Janela.h"
#include <algorithm>
#include "Global.h"
#include "SDL_image.h"

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
	largura_real = 0;
	altura_real = 0;
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

bool Janela::criar(int largura, int altura, bool tela_cheia, string titulo_janela, int sdl_window_flags)
{
	if(criada)
	{
		gDebug.erro("Impossivel criar janela. Uma janela ja existe!");
		return false;
	}

	limparEventos();
	mouse_esta_dentro = false;
	esta_em_foco = false;

	#if UNI_PLATAFORMA_MOVEL
		tela_cheia = true;
	#endif

	if (sdl_window_flags < 0)
		sdl_window_flags = 0;

	//	inicializa video
	if(tela_cheia)
		sdl_window = SDL_CreateWindow(titulo_janela.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, sdl_window_flags | SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		sdl_window = SDL_CreateWindow(titulo_janela.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largura, altura, sdl_window_flags | SDL_WINDOW_SHOWN);

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
	SDL_RenderSetLogicalSize(sdl_renderer, largura, altura);	//	aqui é onde a largura e altura são setadas

	SDL_RenderClear(sdl_renderer);
	SDL_RenderPresent(sdl_renderer);

	this->largura = largura;
	this->altura = altura;

	SDL_GetWindowSize(sdl_window, &largura_real, &altura_real);
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
			largura_real = evento.window.data1;
			altura_real = evento.window.data2;
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

int Janela::getLarguraReal()
{
	return largura_real;
}

int Janela::getAlturaReal()
{
	return altura_real;
}

int Janela::getLarguraTotal()
{
	int larg, alt;
	obterTamanhoTotal(larg, alt);
	return larg;
}

int Janela::getAlturaTotal()
{
	int larg, alt;
	obterTamanhoTotal(larg, alt);
	return alt;
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

void Janela::obterTamanhoReal(int &larg, int &alt)
{
	larg = largura_real;
	alt = altura_real;
}

void Janela::obterTamanhoTotal(int& larg, int& alt)
{
	float razaoLarg = largura / (float)largura_real;
	float razaoAlt = altura / (float)altura_real;

	if (razaoLarg < razaoAlt)		//	tarjas pretas nas laterais 
	{
		float escala = altura / (float)altura_real;
		larg = largura_real * escala;
		alt = altura;
	}
	else if (razaoAlt < razaoLarg)
	{
		larg = largura;
		float escala = largura / (float)largura_real;
		alt = altura_real * escala;
	}
	else
	{
		larg = largura;
		alt = altura;
	}
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
	SDL_RenderSetLogicalSize(sdl_renderer, larg, alt);
	largura = larg;
	altura = alt;
}

void Janela::setTamanhoReal(int larg, int alt)
{
	SDL_SetWindowSize(sdl_window, larg, alt);
	largura_real = larg;
	altura_real = alt;
}

void Janela::setCorDeFundo(const Cor& cor)
{
	this->cor = cor;
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
	{
		SDL_SetWindowFullscreen(sdl_window, 0);
		SDL_SetWindowSize(sdl_window, largura, altura);
		SDL_SetWindowPosition(sdl_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}

	SDL_RenderSetLogicalSize(sdl_renderer, largura, altura);
	SDL_GetWindowSize(sdl_window, &largura_real, &altura_real);
	SDL_GetWindowPosition(sdl_window, &x, &y);
}

void Janela::ajustar()
{
	int l, a;
	if(largura_real > altura_real)
	{
		l = max(largura, altura);
		a = min(largura, altura);
	}
	else
	{
		l = min(largura, altura);
		a = max(largura, altura);
	}
	SDL_RenderSetLogicalSize(sdl_renderer, l, a);
	largura = l;
	altura = a;
}

void Janela::limpar()
{
	SDL_SetRenderDrawBlendMode(sdl_renderer, (cor.a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(sdl_renderer, cor.r, cor.g, cor.b, cor.a);
	SDL_RenderClear(sdl_renderer);
}

void Janela::desenhar()
{
	SDL_RenderPresent(sdl_renderer);
}

void Janela::removerRetanguloDeCorte()
{
	SDL_RenderSetClipRect(sdl_renderer, NULL);
}

void Janela::removerLetterBoxing()
{
	int larg, alt;
	obterTamanhoTotal(larg, alt);
	setTamanho(larg, alt);
}

SDL_Renderer* Janela::getSDL_Renderer()
{
	return sdl_renderer;
}

SDL_Window* Janela::getSDL_Window()
{
	return sdl_window;
}