#include "libUnicornio.h"
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>

SDL_Window *window;
SDL_Renderer *renderer;

bool uni_init = false;

Uint64 tempoAntes;		// tempo em ticks
Uint32 maxFPS;
double framerate;
Uint32 framerateMs;		// framerate em microsegundos
double deltaTempo;

bool telaCheia = false;
int res_x; 
int res_y;
Uint32 clear_color;

GerenciadorDeRecursos recursos;

// depuracao
bool uni_debug = false;
struct debIt
{
	string chave;
	string valor;
};
typedef struct debIt debugItem;
vector<debugItem*> debugMessages;

Fonte* fonte_padrao = NULL;

Eventos eventos;
EventosAplicacao aplicacao;
EventosMouse mouse;
EventosTeclado teclado;
EventosJoysticks joysticks;
EventosToque toques;

bool uniInicializar(int w, int h, bool tela_cheia)
{
	SDL_Init( SDL_INIT_EVERYTHING );

	// Audio: SDL_Mixer
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 1024; //4096
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) 
	{
		// ERRO
	}
	///////

	// Video
	if(tela_cheia)
	{
		window = SDL_CreateWindow("libUNICORNIO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
	{
		window = SDL_CreateWindow("libUNICORNIO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	}

	telaCheia = tela_cheia;

	if(window == nullptr)
	{
        std::cout << SDL_GetError() << std::endl;
        return false;
    }
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE /*| SDL_RENDERER_PRESENTVSYNC*/);

	if(renderer == nullptr)
	{
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

	clear_color = ((255 & 0x0ff) << 24) | ((0 & 0x0ff) << 16) | ((0 & 0x0ff) << 8 ) | ( 0 & 0x0ff);
	Uint8 a = (clear_color >> 24) & 0x0ff;
	Uint8 r = (clear_color >> 16) & 0x0ff;
	Uint8 g = (clear_color >>  8) & 0x0ff;
	Uint8 b = (clear_color) & 0x0ff;

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");  // nao usa nenhum tipo de interpolacao para fazer a escala
	SDL_RenderSetLogicalSize(renderer, w, h);

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	res_x = w; res_y = h;

	TTF_Init();

	uni_init = true;

	//	carrega fonte padrao
	fonte_padrao = new Fonte;
	if(fonte_padrao->carregar("fonte_padrao.ttf", 10) == false)
	{
		fonte_padrao = NULL;
	}

	// inicializa handlers de eventos
	eventos.aplicacao = &aplicacao;
	eventos.mouse = &mouse;
	eventos.teclado = &teclado;
	eventos.joysticks = &joysticks;
	eventos.toques = &toques;
	uniProcessarEventos();

	//	timer
	deltaTempo = 0;
	maxFPS = 60;	//	60 frames por segundo
	framerate = 1.0/maxFPS;
	framerateMs = 1000.0/maxFPS;
	tempoAntes = SDL_GetPerformanceCounter();

	return true;
}

void uniFinalizar()
{
	if(fonte_padrao)
	{
		fonte_padrao->descarregar();
		delete fonte_padrao;
		fonte_padrao = NULL;
	}

	TTF_Quit();
	Mix_CloseAudio();
	while(Mix_Init(0)) Mix_Quit();

	debugItem* temp = NULL;
	for(int i = 0; i < debugMessages.size(); i++)
	{
		temp = debugMessages[i];
		delete temp;
	}

	//	finalializa gerenciador de recursos
	recursos.descarregarTudo();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	uni_init = false;
}

void uniControlarFramerate(bool sleep_loop)
{
	Uint64 tempoAtual = SDL_GetPerformanceCounter();	// tempo em counts
	double deltaTempoMs = ((double)(tempoAtual - tempoAntes)/(double)SDL_GetPerformanceFrequency())*1000.0;	//	deltaTempo em milisegundos
	
	if((deltaTempoMs < framerateMs) && (sleep_loop))
	{
		int delay = (int)framerateMs - (int)deltaTempoMs;	// delay em milisegundos
		while(delay > .0)
		{
			uniDormir(1);
			deltaTempoMs = ((double)(SDL_GetPerformanceCounter() - tempoAntes)/(double)SDL_GetPerformanceFrequency())*1000.0;	//	deltaTempo em milisegundos
			delay = framerateMs - deltaTempoMs;
		}
	}

	deltaTempo = ((double)deltaTempoMs)/1000.0;	//	deltaTempo em segundos.

	tempoAntes = tempoAtual;
}

void uniIniciarFrame(bool sleep_loop)
{
	if(!uni_init) return;

	uniControlarFramerate(sleep_loop);

	uniProcessarEventos();
}

void uniTerminarFrame()
{
	uniDesenharFrame();
}

void uniProcessarEventos()
{
	eventos.atualizar();
}

void uniSetFPS(unsigned int fps) 
{
	maxFPS = fps;
	framerate = 1.0/maxFPS;
	framerateMs = 1000.0/maxFPS;
}

Fonte* uniGetFontePadrao()
{
	if(uni_init)
	{
		return fonte_padrao;
	}

	return NULL;
}

void processarDebug()
{
	if(!uni_debug) return;
	if(debugMessages.size() == 0) return;

	int size_maior_chave = 0;
	int size_maior_valor = 0;

	debugItem* temp = NULL;
	for(int i = 0; i < debugMessages.size(); i++)
	{
		temp = debugMessages[i];

		if(size_maior_chave < temp->chave.size())
			size_maior_chave = temp->chave.size();

		if(size_maior_valor < temp->valor.size())
			size_maior_valor = temp->valor.size();
	}

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = (size_maior_chave*10) + 15 + (size_maior_valor*10);
	rect.h = 30 + debugMessages.size()*10;

	if(rect.w < 200)
		rect.w = 200;

	if(rect.w > res_x)
		rect.w = res_x;

	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 128);
	SDL_RenderFillRect(renderer, &rect);

	Texto t;
	t.setFonte(uniGetFontePadrao());

	t.setTexto("UNICORNIO - Painel de DEBUG");
	t.setAncora(0.5, 0.0);
	t.setCor(255, 255, 255);
	t.desenhar(rect.w/2, 0);

	t.setCor(196, 196, 196);
	int debY = 20;
	for(int i = 0; i < debugMessages.size(); i++)
	{
		temp = debugMessages[i];

		t.setAncora(0.0, 0.0);
		t.setTexto(temp->chave);
		t.desenhar(5, debY);

		t.setAncora(1.0, 0.0);
		t.setTexto(temp->valor);
		t.desenhar(rect.w - 5, debY);

		debY += 10;
	}

}

void uniDepurar(string chave, string valor)
{
	uni_debug = true;
	debugItem* deb = NULL;
	debugItem* temp = NULL;
	for(int i = 0; i < debugMessages.size(); i++)
	{
		temp = debugMessages[i];
		if(temp->chave == chave) deb = temp;
	}
	if(deb == NULL)
	{
		deb = new debugItem;
		deb->chave = chave;
		deb->valor = valor;
		debugMessages.push_back(deb);
	}
	else
	{
		deb->valor = valor;
	}
}

void uniDepurar(string chave, int valor)
{
	string temp;
	stringstream conv;
	conv << valor;
	conv >> temp;
	uniDepurar(chave,temp);
}

void uniDepurar(string chave, double valor)
{
	string temp;
	stringstream conv;
	conv << valor;
	conv >> temp;
	uniDepurar(chave,temp);
}

void uniDepurar(string chave, float valor)
{
	string temp;
	stringstream conv;
	conv << valor;
	conv >> temp;
	uniDepurar(chave,temp);
}

void uniDepurar(string chave, char valor)
{
	string temp;
	stringstream conv;
	conv << valor;
	conv >> temp;
	uniDepurar(chave,temp);
}

void uniErro(string mensagem)
{
	uni_debug = true;
	debugItem* deb;
	deb = new debugItem;
	deb->chave = "ERRO";
	deb->valor = mensagem;
	debugMessages.push_back(deb);
}

void uniSetCorDeFundo(int vermelho, int verde, int azul)
{
	clear_color = ((255 & 0x0ff) << 24) | ((vermelho & 0x0ff) << 16) | ((verde & 0x0ff) << 8 ) | (azul & 0x0ff);
}

void uniDesenharFrame(bool limpa)
{
	if(!uni_init) return;

	processarDebug();

	SDL_RenderPresent(renderer);
	
	if(limpa) 
	{
		Uint8 a = (clear_color >> 24) & 0x0ff;
		Uint8 r = (clear_color >> 16) & 0x0ff;
		Uint8 g = (clear_color >>  8) & 0x0ff;
		Uint8 b = (clear_color) & 0x0ff;

		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		SDL_RenderClear(renderer);		
	}

}

void uniDesenharPixel(int x,int y, int vermelho, int verde, int azul, int opaciade)
{
	if(!uni_init) return;

	Uint8 or, og, ob, oa;

	SDL_SetRenderDrawColor(renderer, (Uint8)vermelho, (Uint8)verde, (Uint8)azul, (Uint8)opaciade); 
	SDL_RenderDrawPoint(renderer, x, y);
}

void uniDesenharLinha(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul, int opaciade)
{
	if(!uni_init) return;

	Uint8 or, og, ob, oa;

	SDL_SetRenderDrawColor(renderer, (Uint8)vermelho, (Uint8)verde, (Uint8)azul, (Uint8)opaciade); 
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2); 
}

void uniDesenharRetangulo(int x, int y, int largura, int altura, int vermelho, int verde, int azul, int opaciade)
{
	if(!uni_init) return;

	Uint8 or, og, ob, oa;

	SDL_SetRenderDrawColor(renderer, (Uint8)vermelho, (Uint8)verde, (Uint8)azul, (Uint8)opaciade); 
	//	Desenha 
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = largura;
	rect.h = altura;
	SDL_RenderDrawRect(renderer, &rect);
}

void uniDormir(int milisec)
{
	SDL_Delay(milisec);
}

void uniDesenharTexto(string txt, int x, int y, int cR, int cG, int cB, bool centralizar)
{
	if(!uni_init) return;

	Texto t;
	t.setFonte(uniGetFontePadrao());
	t.setTexto(txt);
	t.setCor(cR, cG, cB);

	if(!centralizar)
		t.setAncora(0.0, 0.5);

	t.desenhar(x, y);
}

//	Colisao de linhas
bool uniColisaoLinhas(float ax0, float ay0, float ax1, float ay1, float bx0, float by0, float bx1, float by1)
{
	float denominador = ((by1 - by0) * (ax1 - ax0)) - ((bx1 - bx0) * (ay1 - ay0));

	if (denominador == 0)
		return false;

	float ua = (((bx1 - bx0) * (ay0 - by0)) - ((by1 - by0) * (ax0 - bx0))) / denominador;
	float ub = (((ax1 - ax0) * (ay0 - by0)) - ((ay1 - ay0) * (ax0 - bx0))) / denominador;

	if ((ua < 0.0) || (ua > 1.0) || (ub < 0.0) || (ub > 1.0))
		return false;

	return true;
}

//	colisao entre ponto e retangulo
bool uniColisaoPontoRetangulo(int ponto_x, int ponto_y, int x, int y, float rot, int largura, int altura, float ancora_x, float ancora_y)
{
	//	invez de rotacionar o retangulo, transladar, e calcular se o ponto está dentro dele
	//	vamos transladar o retangulo, rotacionar o ponto e calcular se o ponto está dentro do retangulo
	//	essa abordagem é muito mais simples e rápida, pois o retangulo fica alinhado aos eixos, facilitando o calculo

	//	primeiro translada o retangulo para a origem
	SDL_Rect rect;
	rect.w = largura;
	rect.h = altura;
	rect.x = -ancora_x*rect.w;
	rect.y = -ancora_y*rect.h;

	//	depois, translada o ponto para a origem e rotaciona ao contrario
	SDL_Point vec = {ponto_x - x, ponto_y - y};

	float rad = (-rot)*PI/180;	//	rotação ao contrario
	float cs = cos(rad);
	float sn = sin(rad);

	ponto_x = vec.x * cs - vec.y * sn;
	ponto_y = vec.x * sn + vec.y * cs;

	//	por fim, calcula se o ponto está dentro do retangulo
	return ( (ponto_x <= rect.x + rect.w) && (ponto_x >= rect.x) && (ponto_y <= rect.y + rect.h) && (ponto_y >= rect.y) );
}

//	Colisao de retangulos
bool uniColisaoRetangulos(int x1, int y1, float rot1, int largura1, int altura1, float ancora_x1, float ancora_y1, int x2, int y2, float rot2, int largura2, int altura2, float ancora_x2, float ancora_y2)
{

	//	1) calcula linhas do retangulo 1
	//	coloca a ancora do retangulo na origem
	SDL_Rect retan;
	retan.x = -ancora_x1*largura1;
	retan.y = -ancora_y1*altura1;
	retan.w = largura1;
	retan.h = altura1;

	SDL_Point pontos[4];
	pontos[0].x = retan.x;			 pontos[0].y = retan.y;
	pontos[1].x = retan.x + retan.w; pontos[1].y = retan.y;
	pontos[2].x = retan.x + retan.w; pontos[2].y = retan.y + retan.h;
	pontos[3].x = retan.x;			 pontos[3].y = retan.y + retan.h;

	float rad = rot1*PI/180;
	float cs = cos(rad);
	float sn = sin(rad);

	for(int i = 0; i < 4; ++i)
	{
		//	rotaciona os pontos (em relação a origem)
		float xx = pontos[i].x * cs - pontos[i].y * sn;
		float yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos de volta
		pontos[i].x = xx + x1;
		pontos[i].y = yy + y1;
	}

	//	calcula as 4 linhas do retangulo
	SDL_Point linhasA[4][2];	// 4 linhas, cada uma com 2 pontos
	linhasA[0][0] = pontos[0];
	linhasA[0][1] = pontos[1];
	linhasA[1][0] = pontos[1];
	linhasA[1][1] = pontos[2];
	linhasA[2][0] = pontos[2];
	linhasA[2][1] = pontos[3];
	linhasA[3][0] = pontos[3];
	linhasA[3][1] = pontos[0];

	//	2) calcula linhas do retangulo 2
	//	coloca a ancora do retangulo na origem
	retan.x = -ancora_x2*largura2;
	retan.y = -ancora_y2*altura2;
	retan.w = largura2;
	retan.h = altura2;

	pontos[0].x = retan.x;			 pontos[0].y = retan.y;
	pontos[1].x = retan.x + retan.w; pontos[1].y = retan.y;
	pontos[2].x = retan.x + retan.w; pontos[2].y = retan.y + retan.h;
	pontos[3].x = retan.x;			 pontos[3].y = retan.y + retan.h;

	rad = rot2*PI/180;
	cs = cos(rad);
	sn = sin(rad);

	for(int i = 0; i < 4; ++i)
	{
		//	rotaciona os pontos (em relação a origem)
		float xx = pontos[i].x * cs - pontos[i].y * sn;
		float yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos de volta
		pontos[i].x = xx + x2;
		pontos[i].y = yy + y2;
	}

	//	calcula as 4 linhas do retangulo
	SDL_Point linhasB[4][2];	// 4 linhas, cada uma com 2 pontos
	linhasB[0][0] = pontos[0];
	linhasB[0][1] = pontos[1];
	linhasB[1][0] = pontos[1];
	linhasB[1][1] = pontos[2];
	linhasB[2][0] = pontos[2];
	linhasB[2][1] = pontos[3];
	linhasB[3][0] = pontos[3];
	linhasB[3][1] = pontos[0];

	//	testa intersecção entre as linhas de um retangulo contra as linhas do outro
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			if(uniColisaoLinhas(linhasA[i][0].x, linhasA[i][0].y, linhasA[i][1].x, linhasA[i][1].y, 
								linhasB[j][0].x, linhasB[j][0].y, linhasB[j][1].x, linhasB[j][1].y))
				return true;
		}
	}

	//	se não ouve nenhuma intersecção
	//	pode ser que um retangulo esteja totalmente dentro do outro,
	//	então testa este caso

	return (uniColisaoPontoRetangulo(x1, y1, x2, y2, rot2, largura2, altura2, ancora_x2, ancora_y2) 
		|| 	uniColisaoPontoRetangulo(x2, y2, x1, y1, rot1, largura1, altura1, ancora_x1, ancora_y1));
}

bool uniColisao(int px, int py, Sprite* spr, int spr_x, int spr_y, float spr_rot)
{
	int larg, alt;
	float ax, ay;
	spr->obterTamanho(larg, alt);
	spr->obterAncora(ax, ay);

	return uniColisaoPontoRetangulo(px, py, spr_x, spr_y, spr_rot, larg, alt, ax, ay);
}

bool uniColisao(Sprite* spr1, int x1, int y1, float rot1, Sprite* spr2, int x2, int y2, float rot2)
{
	int larg1, alt1, larg2, alt2;
	float ax1, ay1, ax2, ay2;
	spr1->obterTamanho(larg1, alt1);
	spr1->obterAncora(ax1, ay1);
	spr2->obterTamanho(larg2, alt2);
	spr2->obterAncora(ax2, ay2);

	return uniColisaoRetangulos(x1, y1, rot1, larg1, alt1, ax1, ay1, x2, y2, rot2, larg2, alt2, ax2, ay2);
}