#include "libUnicornio.h"
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>

SDL_Window *window;
SDL_Renderer *renderer;
int res_x; 
int res_y;
bool telaCheia = false;
Uint32 clear_color;

bool uni_init = false;
bool uni_debug = false;

double deltaTempo;
Uint64 tempoAntes;		// tempo em ticks
Uint32 maxFPS;
double framerate;
Uint32 framerateMs;		// framerate em microsegundos

GerenciadorDeRecursos recursos;

// depuracao
struct ItemDebug
{
	string chave;
	string valor;
};

vector<ItemDebug*> mensagensDebug;

Fonte* fonte_padrao = NULL;

Eventos eventos;
EventosAplicacao aplicacao;
EventosMouse mouse;
EventosTeclado teclado;
EventosJoysticks joysticks;
EventosToque toques;

bool uniInicializar(int resolucao_x, int resolucao_y, bool tela_cheia, string titulo_janela)
{
	//	inicializa SDL
	SDL_Init( SDL_INIT_EVERYTHING );

	//	inicializa video
	if(tela_cheia)
		window = SDL_CreateWindow(titulo_janela.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		window = SDL_CreateWindow(titulo_janela.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resolucao_x, resolucao_y, SDL_WINDOW_SHOWN);

	if(window == NULL)
	{
        //	ERRO
        return false;
    }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE /*| SDL_RENDERER_PRESENTVSYNC*/);

	if(renderer == NULL)
	{
        //	ERRO
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
	SDL_RenderSetLogicalSize(renderer, resolucao_x, resolucao_y);

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	telaCheia = tela_cheia;
	res_x = resolucao_x; 
	res_y = resolucao_y;

	//	inicializa audio
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 1024; //4096
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) 
	{
		// ERRO
		return false;
	}

	//	inicializa biblioteca de fontes
	TTF_Init();
	
	//	seta uni_init para true. Precisa ser feito aqui para poder carregar a fonte padrao
	uni_init = true;

	//	carrega fonte padrao
	fonte_padrao = new Fonte;
	if(fonte_padrao->carregar("fonte_padrao.ttf", 10) == false)
	{
		fonte_padrao = NULL;
	}

	//	inicializa handlers de eventos
	eventos.aplicacao = &aplicacao;
	eventos.mouse = &mouse;
	eventos.teclado = &teclado;
	eventos.joysticks = &joysticks;
	eventos.toques = &toques;
	uniProcessarEventos();

	//	inicializa variaveis de tempo
	deltaTempo = 0;
	maxFPS = 60;	//	60 frames por segundo
	framerate = 1.0/maxFPS;
	framerateMs = 1000.0/maxFPS;
	tempoAntes = SDL_GetPerformanceCounter();

	return true;
}

void uniFinalizar()
{
	//	finaliza mensagens de debug
	for(unsigned int i = 0; i < mensagensDebug.size(); i++)
	{
		delete mensagensDebug[i];
	}
	mensagensDebug.clear();

	//	finaliza gerenciador de recursos
	recursos.descarregarTudo();

	//	finaliza fonte padrao
	if(fonte_padrao)
	{
		fonte_padrao->descarregar();
		delete fonte_padrao;
		fonte_padrao = NULL;
	}

	// finaliza biblioteca de fontes
	TTF_Quit();

	// finaliza audio
	Mix_CloseAudio();
	while(Mix_Init(0)) Mix_Quit();

	//	finaliza video
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//	finaliza SDL
	SDL_Quit();

	//	seta uni_init para false
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

unsigned int uniGetFPS()
{
	return maxFPS;
}

void uniSetFPS(unsigned int fps) 
{
	maxFPS = fps;
	framerate = 1.0/maxFPS;
	framerateMs = 1000.0/maxFPS;
}

string uniGetTituloJanela()
{
	return SDL_GetWindowTitle(window);
}

void uniSetTituloJanela(string titulo_janela)
{
	SDL_SetWindowTitle(window, titulo_janela.c_str());
}

void uniSetIconeJanela(string arquivo)
{
	SDL_Surface *surface = IMG_Load(arquivo.c_str());
	if(surface)
	{
		SDL_SetWindowIcon(window, surface);
		SDL_FreeSurface(surface);
	}
}

bool uniEstaEmModoTelaCheia()
{
	return telaCheia;
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
	if(mensagensDebug.size() == 0) return;

	unsigned int size_maior_chave = 0;
	unsigned int size_maior_valor = 0;

	ItemDebug* temp = NULL;
	for(unsigned int i = 0; i < mensagensDebug.size(); i++)
	{
		temp = mensagensDebug[i];

		if(size_maior_chave < temp->chave.size())
			size_maior_chave = temp->chave.size();

		if(size_maior_valor < temp->valor.size())
			size_maior_valor = temp->valor.size();
	}

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = (size_maior_chave*10) + 15 + (size_maior_valor*10);
	rect.h = 30 + mensagensDebug.size()*10;

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
	for(unsigned int i = 0; i < mensagensDebug.size(); i++)
	{
		temp = mensagensDebug[i];

		t.setAncora(0.0, 0.0);
		t.setTexto(temp->chave);
		t.desenhar(5, debY);

		t.setAncora(1.0, 0.0);
		t.setTexto(temp->valor);
		t.desenhar(rect.w - 5, debY);

		debY += 10;
	}

}

void uniDormir(int milisec)
{
	SDL_Delay(milisec);
}

void uniErro(string mensagem)
{
	uni_debug = true;
	ItemDebug* deb;
	deb = new ItemDebug;
	deb->chave = "ERRO";
	deb->valor = mensagem;
	mensagensDebug.push_back(deb);
}

void uniDepurar(string chave, string valor)
{
	uni_debug = true;
	ItemDebug* deb = NULL;
	ItemDebug* temp = NULL;
	for(unsigned int i = 0; i < mensagensDebug.size(); i++)
	{
		temp = mensagensDebug[i];
		if(temp->chave == chave) deb = temp;
	}
	if(deb == NULL)
	{
		deb = new ItemDebug;
		deb->chave = chave;
		deb->valor = valor;
		mensagensDebug.push_back(deb);
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

void uniSetCorDeFundo(int vermelho, int verde, int azul)
{
	clear_color = ((255 & 0x0ff) << 24) | ((vermelho & 0x0ff) << 16) | ((verde & 0x0ff) << 8 ) | (azul & 0x0ff);
}

void uniDesenharPixel(int x,int y, int vermelho, int verde, int azul, int opaciade)
{
	if(!uni_init) return;

	SDL_SetRenderDrawColor(renderer, (Uint8)vermelho, (Uint8)verde, (Uint8)azul, (Uint8)opaciade); 
	SDL_RenderDrawPoint(renderer, x, y);
}

void uniDesenharLinha(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul, int opaciade)
{
	if(!uni_init) return;

	SDL_SetRenderDrawColor(renderer, (Uint8)vermelho, (Uint8)verde, (Uint8)azul, (Uint8)opaciade); 
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2); 
}

void uniDesenharCirculo(int x, int y, float raio, int num_segmentos, int vermelho, int verde, int azul)
{
	float c, s;

	int anterior_x = x + raio;
	int anterior_y = y;

	//	desenha borda
	float numLinhas = 120;	// numero de linhas para desenhar a borda do circulo
	for(float i = 0; i <= 360; i += 360.0f/(float)num_segmentos)
	{
		c = cos(i*PI/180);
		s = sin(i*PI/180);

		int atual_x = x + c*raio;
		int atual_y = y + s*raio;

		uniDesenharLinha(anterior_x, anterior_y, atual_x, atual_y, vermelho, verde, azul);

		anterior_x = atual_x;
		anterior_y = atual_y;
	}
}

void uniDesenharRetangulo(int x, int y, float rot, int largura, int altura, float ancora_x, float ancora_y, int vermelho, int verde, int azul)
{
	float cs = cos(rot*PI/180.0);
	float sn = sin(rot*PI/180.0);

	float meiaLargura = (float)largura*ancora_x;
	float meiaAltura = (float)altura*ancora_y;

	SDL_Point pontos[4];

	pontos[0].x = -largura*ancora_x;		pontos[0].y = -altura*ancora_y;
	pontos[1].x = pontos[0].x + largura;	pontos[1].y = pontos[0].y;
	pontos[2].x = pontos[1].x;				pontos[2].y = pontos[0].y + altura;
	pontos[3].x = pontos[0].x;				pontos[3].y = pontos[2].y;

	for(int i = 0; i < 4; ++i)
	{
		//	rotaciona os pontos (em relação a origem)
		float xx = pontos[i].x * cs - pontos[i].y * sn;
		float yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos para posição
		pontos[i].x = xx + x;
		pontos[i].y = yy + y;
	}

	uniDesenharLinha(pontos[0].x, pontos[0].y, pontos[1].x, pontos[1].y, vermelho, verde, azul);
	uniDesenharLinha(pontos[1].x, pontos[1].y, pontos[2].x, pontos[2].y, vermelho, verde, azul);
	uniDesenharLinha(pontos[2].x, pontos[2].y, pontos[3].x, pontos[3].y, vermelho, verde, azul);
	uniDesenharLinha(pontos[3].x, pontos[3].y, pontos[0].x, pontos[0].y, vermelho, verde, azul);
}

void uniDesenharPoligono(int x, int y, float rot, float escala_x, float escala_y, Vetor2D* pontos, int num_pontos, int vermelho, int verde, int azul)
{
	if(num_pontos < 3)
		return;

	float cs = cos(rot*PI/180.0);
	float sn = sin(rot*PI/180.0);

	float xx = (pontos[0].x*escala_x) * cs - (pontos[0].y*escala_y) * sn;
	float yy = (pontos[0].x*escala_x) * sn + (pontos[0].y*escala_y) * cs;

	int x_anterior = xx + x;
	int y_anterior = yy + y;

	int primeiro_x = x_anterior;
	int primeiro_y = y_anterior;

	for(int i = 1; i < num_pontos; ++i)
	{
		//	rotaciona os pontos (em relação a origem)
		xx = (pontos[i].x*escala_x) * cs - (pontos[i].y*escala_y) * sn;
		yy = (pontos[i].x*escala_x) * sn + (pontos[i].y*escala_y) * cs;

		//	translada os pontos para posição
		int x_atual = xx + x;
		int y_atual = yy + y;

		uniDesenharLinha(x_anterior, y_anterior, x_atual, y_atual, vermelho, verde, azul);

		x_anterior = x_atual;
		y_anterior = y_atual;
	}

	uniDesenharLinha(x_anterior, y_anterior, primeiro_x, primeiro_y, vermelho, verde, azul);
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

//	func de colisao entre ponto e Sprite - VAI SER REMOVIDA NO FUTURO
bool uniColisao(int px, int py, Sprite* spr, int spr_x, int spr_y, float spr_rot)
{
	return uniColisaoPontoComSprite(px, py, spr, spr_x, spr_y, spr_rot);
}

//	func de colisao entre sprites - VAI SER REMOVIDA NO FUTURO
bool uniColisao(Sprite* spr1, int x1, int y1, float rot1, Sprite* spr2, int x2, int y2, float rot2)
{
	return uniColisaoSpriteComSprite(spr1, x1, y1, rot1, spr2, x2, y2, rot2, true);
}

//	colisaor entre ponto e circulo
bool uniColisaoPontoComCirculo(float ponto_x, float ponto_y, float circulo_x, float circulo_y, float raio)
{
	float dist_ao_quadrado = (ponto_x - circulo_x)*(ponto_x - circulo_x) + (ponto_y - circulo_y)*(ponto_y - circulo_y);

	return (dist_ao_quadrado < raio*raio);
}

//	colisao entre ponto e retangulo
bool uniColisaoPontoComRetangulo(int ponto_x, int ponto_y, int x, int y, float rot, int largura, int altura, float ancora_x, float ancora_y)
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

//	colisao entre ponto e poligono
bool uniColisaoPontoComPoligono(float ponto_x, float ponto_y, Vetor2D* pontos, int num_pontos, float x, float y, float rot, float escala_x, float escala_y)
{
	//	se nao tiver pontos suficientes, nao testa
	if(num_pontos < 3)
		return false;

	Vetor2D* poli = new Vetor2D[num_pontos];

	//	calcula rot(em radianos), seno e cosseno
	float rad = rot*PI/180;
	float cs = cos(rad);
	float sn = sin(rad);

	//	rotaciona os pontos (em relação a origem)
	float xx = (pontos[0].x*escala_x) * cs - (pontos[0].y*escala_y) * sn;
	float yy = (pontos[0].x*escala_x) * sn + (pontos[0].y*escala_y) * cs;

	//	translada os pontos de volta
	poli[0].x = xx + x;
	poli[0].y = yy + y;

	Vetor2D menor, maior;
	maior = menor = poli[0];

	//	calcula os pontos
	for(int i = 1; i < num_pontos; ++i)
	{
		//	rotaciona os pontos (em relação a origem)
		float xx = (pontos[i].x*escala_x) * cs - (pontos[i].y*escala_y) * sn;
		float yy = (pontos[i].x*escala_x) * sn + (pontos[i].y*escala_y) * cs;

		//	translada os pontos de volta
		poli[i].x = xx + x;
		poli[i].y = yy + y;

		//	calcula AABB (para um primeiro teste)
		menor.x = std::min(menor.x, poli[i].x);
		menor.y = std::min(menor.y, poli[i].y);
		maior.x = std::max(maior.x, poli[i].x);
		maior.y = std::max(maior.y, poli[i].y);
	}

	//	testa AABB 
	if(ponto_x < menor.x || ponto_x > maior.x || ponto_y < menor.y || ponto_y > maior.y)
        return false;

	//	Usa algoritmo 'pnpoly' http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
    bool dentro = false;
	for(int i = 0, j = num_pontos-1 ; i < num_pontos; j = i++)
    {
        if((poli[i].y > ponto_y ) != (poli[j].y > ponto_y ) &&
			ponto_x < (poli[j].x - poli[i].x)*(ponto_y - poli[i].y)/(poli[j].y - poli[i].y) + poli[i].x)
			{
				dentro = !dentro;
			}
    }

	delete[] poli;
    return dentro;
}

bool uniColisaoPontoComSprite(float ponto_x, float ponto_y, Sprite* spr, float x, float y, float rot)
{
	float ax, ay;
	int larg, alt;

	spr->obterAncora(ax, ay);
	spr->obterTamanho(larg, alt);

	return uniColisaoPontoComRetangulo(ponto_x, ponto_y, x, y, rot, larg, alt, ax, ay);
}

bool uniColisaoLinhaComLinha(float linhaA_x0, float linhaA_y0, float linhaA_x1, float linhaA_y1, float linhaB_x0, float linhaB_y0, float linhaB_x1, float linhaB_y1)
{
	float denominador = ((linhaB_y1 - linhaB_y0) * (linhaA_x1 - linhaA_x0)) - ((linhaB_x1 - linhaB_x0) * (linhaA_y1 - linhaA_y0));

	if (denominador == 0)
		return false;

	float ua = (((linhaB_x1 - linhaB_x0) * (linhaA_y0 - linhaB_y0)) - ((linhaB_y1 - linhaB_y0) * (linhaA_x0 - linhaB_x0))) / denominador;
	float ub = (((linhaA_x1 - linhaA_x0) * (linhaA_y0 - linhaB_y0)) - ((linhaA_y1 - linhaA_y0) * (linhaA_x0 - linhaB_x0))) / denominador;

	if ((ua < 0.0) || (ua > 1.0) || (ub < 0.0) || (ub > 1.0))
		return false;

	return true;
}

bool uniColisaoLinhaComCirculo(float linha_x1, float linha_y1, float linha_x2, float linha_y2, float circulo_x, float circulo_y, float raio)
{
	//	translada pontos da linha para ficarem em relacao ao centro do circulo
	float p1_x = linha_x1 - circulo_x;
	float p1_y = linha_y1 - circulo_y;

	float p2_x = linha_x2 - circulo_x;
	float p2_y = linha_y2 - circulo_y;

	//	calcula a distancia entre esses pontos
	float dx = p2_x - p1_x;
	float dy = p2_y - p1_y;

	//	calcula 'a', 'b' e 'c' da equacao de baskara
	float a = (dx*dx) + (dy*dy);
	float b = 2 * ((p1_x*dx) + (p1_y*dy));
	float c = (p1_x*p1_x) + (p1_y*p1_y) - (raio*raio);

	//	calcula 'delta' da equacao de baskara
	float delta = (b*b) - (4*a*c);

	//	se delta < 0. Nao tem interseccao
	if(delta < 0)
		return false;

	//	se delta == 0. Tem uma interseccao
	if(delta == 0)
	{
		float u = -b/(2*a);

		return !(u < 0.0f || u > 1.0f);
	}

	//	se delta > 0. Tem duas interseccoes
	float raiz_quadrada_delta = sqrt(delta);

	float u1 = (-b + raiz_quadrada_delta)/(2*a);
	float u2 = (-b - raiz_quadrada_delta)/(2*a);

	return ((u1 >= 0.0f && u1 <= 1.0f) || (u2 >= 0.0f && u2 <= 1.0f));
}

//	colisao entre linha e retangulo
bool uniColisaoLinhaComRetangulo(float linha_x1, float linha_y1, float linha_x2, float linha_y2, int retan_x, int retan_y, float retan_rot, int retan_largura, int retan_altura, float retan_ancora_x, float retan_ancora_y)
{
	SDL_Rect retan;
	retan.x = -retan_ancora_x*retan_largura;
	retan.y = -retan_ancora_y*retan_altura;
	retan.w = retan_largura;
	retan.h = retan_altura;

	SDL_Point pontos[4];
	pontos[0].x = retan.x;			 pontos[0].y = retan.y;
	pontos[1].x = retan.x + retan.w; pontos[1].y = retan.y;
	pontos[2].x = retan.x + retan.w; pontos[2].y = retan.y + retan.h;
	pontos[3].x = retan.x;			 pontos[3].y = retan.y + retan.h;

	float rad = retan_rot*PI/180;
	float cs = cos(rad);
	float sn = sin(rad);

	for(int i = 0; i < 4; ++i)
	{
		//	rotaciona os pontos (em relação a origem)
		float xx = pontos[i].x * cs - pontos[i].y * sn;
		float yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos de volta
		pontos[i].x = xx + retan_x;
		pontos[i].y = yy + retan_y;
	}

	for(int i = 0; i < 4; ++i)
	{
		int j = (i+1)%4;
		if(uniColisaoLinhaComLinha(linha_x1, linha_y1, linha_x2, linha_y2,
								   pontos[i].x, pontos[i].y, pontos[j].x, pontos[j].y))
			return true;
	}

	return false;
}

//	colisao entre linha e poligono
bool uniColisaoLinhaComPoligono(float linha_x1, float linha_y1, float linha_x2, float linha_y2, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, float poli_escala_x, float poli_escala_y)
{
	//	se nao tiver pontos suficientes, nao testa
	if(num_pontos < 3)
		return false;

	//	calcula rot(em radianos), seno e cosseno
	float rad = poli_rot*PI/180;
	float cs = cos(rad);
	float sn = sin(rad);

	float xx_ant;
	float yy_ant;
	float xx;
	float yy;

	xx = ((pontos[0].x*poli_escala_x) * cs - (pontos[0].y*poli_escala_y) * sn) + poli_x;
	yy = ((pontos[0].x*poli_escala_x) * sn + (pontos[0].y*poli_escala_y) * cs) + poli_y;

	for(int i = 0; i < num_pontos; ++i)
	{
		xx_ant = xx;
		yy_ant = yy;

		int j = (i+1)%num_pontos;

		xx = ((pontos[j].x*poli_escala_x) * cs - (pontos[j].y*poli_escala_y) * sn) + poli_x;
		yy = ((pontos[j].x*poli_escala_x) * sn + (pontos[j].y*poli_escala_y) * cs) + poli_y;

		if(uniColisaoLinhaComLinha(linha_x1, linha_y1, linha_x2, linha_y2, xx_ant, yy_ant, xx, yy))
		{
			return true;
		}
	}

	return false;
}

//	colisao entre linha e sprite
bool uniColisaoLinhaComSprite(float linha_x1, float linha_y1, float linha_x2, float linha_y2, Sprite* spr, float x, float y, float rot)
{
	float ax, ay;
	int larg, alt;

	spr->obterAncora(ax, ay);
	spr->obterTamanho(larg, alt);

	return uniColisaoLinhaComRetangulo(linha_x1, linha_y1, linha_x2, linha_y2, x, y, rot, larg, alt, ax, ay);
}

//	colisao entre circulos
bool uniColisaoCirculoComCirculo(float cx1, float cy1, float raio1, float cx2, float cy2, float raio2)
{
	float dist_ao_quadrado = (cx1 - cx2)*(cx1 - cx2) + (cy1 - cy2)*(cy1 - cy2);
	float soma_dos_raios = raio1+raio2;

	return (dist_ao_quadrado < soma_dos_raios*soma_dos_raios);
}

//	colisao entre circulo e retangulo
bool uniColisaoCirculoComRetangulo(float circulo_x, float circulo_y, float raio, int retan_x, int retan_y, float retan_rot, int retan_largura, int retan_altura, float retan_ancora_x, float retan_ancora_y, bool testar_dentro)
{
	SDL_Rect retan;
	retan.x = -retan_ancora_x*retan_largura;
	retan.y = -retan_ancora_y*retan_altura;
	retan.w = retan_largura;
	retan.h = retan_altura;

	SDL_Point pontos[4];
	pontos[0].x = retan.x;			 pontos[0].y = retan.y;
	pontos[1].x = retan.x + retan.w; pontos[1].y = retan.y;
	pontos[2].x = retan.x + retan.w; pontos[2].y = retan.y + retan.h;
	pontos[3].x = retan.x;			 pontos[3].y = retan.y + retan.h;

	float rad = retan_rot*PI/180;
	float cs = cos(rad);
	float sn = sin(rad);

	for(int i = 0; i < 4; ++i)
	{
		//	rotaciona os pontos (em relação a origem)
		float xx = pontos[i].x * cs - pontos[i].y * sn;
		float yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos de volta
		pontos[i].x = xx + retan_x;
		pontos[i].y = yy + retan_y;
	}

	bool colidiu = false;
	for(int i = 0; i < 4 && !colidiu; ++i)
	{
		int j = (i+1)%4;
		colidiu = uniColisaoLinhaComCirculo(pontos[i].x, pontos[i].y, pontos[j].x, pontos[j].y, circulo_x, circulo_y, raio);
	}

	if(!colidiu && testar_dentro)
	{
		colidiu = uniColisaoPontoComCirculo(retan_x, retan_y, circulo_x, circulo_y, raio) 
			|| uniColisaoPontoComRetangulo(circulo_x, circulo_y, retan_x, retan_y, retan_rot, retan_largura, retan_altura, retan_ancora_x, retan_ancora_y);
	}

	return colidiu;
}

//	colisao entre circulo e poligono
bool uniColisaoCirculoComPoligono(float circulo_x, float circulo_y, float raio, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, float poli_escala_x, float poli_escala_y, bool testar_dentro)
{
	//	se nao tiver pontos suficientes, nao testa
	if(num_pontos < 3)
		return false;

	//	calcula rot(em radianos), seno e cosseno
	float rad = poli_rot*PI/180;
	float cs = cos(rad);
	float sn = sin(rad);

	float xx_ant;
	float yy_ant;
	float xx;
	float yy;

	xx = ((pontos[0].x*poli_escala_x) * cs - (pontos[0].y*poli_escala_y) * sn) + poli_x;
	yy = ((pontos[0].x*poli_escala_x) * sn + (pontos[0].y*poli_escala_y) * cs) + poli_y;

	bool colidiu = false;
	for(int i = 0; i < num_pontos && !colidiu; ++i)
	{
		xx_ant = xx;
		yy_ant = yy;

		int j = (i+1)%num_pontos;

		xx = ((pontos[j].x*poli_escala_x) * cs - (pontos[j].y*poli_escala_y) * sn) + poli_x;
		yy = ((pontos[j].x*poli_escala_x) * sn + (pontos[j].y*poli_escala_y) * cs) + poli_y;

		colidiu = uniColisaoLinhaComCirculo(xx_ant, yy_ant, xx, yy, circulo_x, circulo_y, raio);
	}

	if(!colidiu && testar_dentro)
	{
		colidiu = uniColisaoPontoComCirculo(poli_x, poli_y, circulo_x, circulo_y, raio) 
			|| uniColisaoPontoComPoligono(circulo_x, circulo_y, pontos, num_pontos, poli_x, poli_y, poli_rot, poli_escala_x, poli_escala_y);
	}

	return colidiu;
}

//	colisao entre circulo e sprite
bool uniColisaoCirculoComSprite(float circulo_x, float circulo_y, float raio, Sprite* spr, float x, float y, float rot, bool testar_dentro)
{
	float ax, ay;
	int larg, alt;

	spr->obterAncora(ax, ay);
	spr->obterTamanho(larg, alt);

	return uniColisaoCirculoComRetangulo(circulo_x, circulo_y, raio, x, y, rot, larg, alt, ax, ay, testar_dentro);
}

//	colisao entre retangulos
bool uniColisaoRetanguloComRetangulo(int x1, int y1, float rot1, int largura1, int altura1, float ancora_x1, float ancora_y1, int x2, int y2, float rot2, int largura2, int altura2, float ancora_x2, float ancora_y2, bool testar_dentro)
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
	bool colidiu = false;
	for(int i = 0; i < 4 && !colidiu; ++i)
	{
		for(int j = 0; j < 4 && !colidiu; ++j)
		{
			colidiu = uniColisaoLinhaComLinha(linhasA[i][0].x, linhasA[i][0].y, linhasA[i][1].x, linhasA[i][1].y, 
											  linhasB[j][0].x, linhasB[j][0].y, linhasB[j][1].x, linhasB[j][1].y);
		}
	}

	//	se não ouve nenhuma intersecção
	//	pode ser que um retangulo esteja totalmente dentro do outro,
	//	então testa este caso

	if(!colidiu && testar_dentro)
	{
		colidiu = uniColisaoPontoComRetangulo(x1, y1, x2, y2, rot2, largura2, altura2, ancora_x2, ancora_y2) 
			   || uniColisaoPontoComRetangulo(x2, y2, x1, y1, rot1, largura1, altura1, ancora_x1, ancora_y1);
	}

	return colidiu;
}

//	colisao entre retangulo e poligono
bool uniColisaoRetanguloComPoligono(int retan_x, int retan_y, float retan_rot, int retan_largura, int retan_altura, float retan_ancora_x, float retan_ancora_y, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, float poli_escala_x, float poli_escala_y, bool testar_dentro)
{
	Vetor2D retan[4];
	retan[0].x = -retan_ancora_x*retan_largura;
	retan[0].y = -retan_ancora_y*retan_altura;
	retan[1].x = retan[0].x + retan_largura;
	retan[1].y = retan[0].y;
	retan[2].x = retan[1].x;
	retan[2].y = retan[0].y + retan_altura;
	retan[3].x = retan[0].x;
	retan[3].y = retan[2].y;

	return uniColisaoPoligonoComPoligono(pontos, num_pontos, poli_x, poli_y, poli_rot, poli_escala_x, poli_escala_y, retan, 4, retan_x, retan_y, retan_rot, 1, 1, testar_dentro);
}

//	colisao entre retangulo e sprite
bool uniColisaoRetanguloComSprite(int retan_x, int retan_y, float retan_rot, int retan_largura, int retan_altura, float retan_ancora_x, float retan_ancora_y, Sprite* spr, float x, float y, float rot, bool testar_dentro)
{
	float ax, ay;
	int larg, alt;

	spr->obterAncora(ax, ay);
	spr->obterTamanho(larg, alt);

	return uniColisaoRetanguloComRetangulo(retan_x, retan_y, retan_rot, retan_largura, retan_altura, retan_ancora_x, retan_ancora_y, x, y, rot, larg, alt, ax, ay, testar_dentro);
}

//	colisao entre poligonos
bool uniColisaoPoligonoComPoligono(Vetor2D* pontos1, int num_pontos1, float x1, float y1, float rot1, float escala_x1, float escala_y1, Vetor2D* pontos2, int num_pontos2, float x2, float y2, float rot2, float escala_x2, float escala_y2, bool testar_dentro)
{
	//	se nao tiver pontos suficientes, nao testa
	if(num_pontos1 < 3 || num_pontos2 < 3)
		return false;

	//	calcula rot(em radianos), seno e cosseno
	float rad1 = rot1*PI/180;
	float cs1 = cos(rad1);
	float sn1 = sin(rad1);

	float rad2 = rot2*PI/180;
	float cs2 = cos(rad2);
	float sn2 = sin(rad2);

	//	testa cada uma das linhas
	bool colidiu = false;

	float poli1_xx = ((pontos1[0].x*escala_x1) * cs1 - (pontos1[0].y*escala_y1) * sn1) + x1;
	float poli1_yy = ((pontos1[0].x*escala_x1) * sn1 + (pontos1[0].y*escala_y1) * cs1) + y1;
	float poli1_xx_ant;
	float poli1_yy_ant;

	for(int i = 0; i < num_pontos1 && !colidiu; ++i)
	{
		poli1_xx_ant = poli1_xx;
		poli1_yy_ant = poli1_yy;

		int ii = (i+1)%num_pontos1;

		float poli1_xx = ((pontos1[ii].x*escala_x1) * cs1 - (pontos1[ii].y*escala_y1) * sn1) + x1;
		float poli1_yy = ((pontos1[ii].x*escala_x1) * sn1 + (pontos1[ii].y*escala_y1) * cs1) + y1;

		float poli2_xx = ((pontos2[0].x*escala_x2) * cs2 - (pontos2[0].y*escala_y2) * sn2) + x2;
		float poli2_yy = ((pontos2[0].x*escala_x2) * sn2 + (pontos2[0].y*escala_y2) * cs2) + y2;
		float poli2_xx_ant;
		float poli2_yy_ant;

		for(int j = 0; j < num_pontos2; ++j)
		{		
			poli2_xx_ant = poli2_xx;
			poli2_yy_ant = poli2_yy;

			int jj = (j+1)%num_pontos2;

			float poli2_xx = ((pontos2[jj].x*escala_x2) * cs2 - (pontos2[jj].y*escala_y2) * sn2) + x2;
			float poli2_yy = ((pontos2[jj].x*escala_x2) * sn2 + (pontos2[jj].y*escala_y2) * cs2) + y2;

			if(uniColisaoLinhaComLinha(poli1_xx_ant, poli1_yy_ant, poli1_xx, poli1_yy, 
									   poli2_xx_ant, poli2_yy_ant, poli2_xx, poli2_yy))
			{
				colidiu = true;
				break;
			}
		}
	}

	//	se não ouve nenhuma intersecção
	//	pode ser que um poligono esteja totalmente dentro do outro,
	//	então testa este caso

	if(!colidiu && testar_dentro)
	{
		colidiu = uniColisaoPontoComPoligono(x1, y1, pontos2, num_pontos2, x2, y2, rot2, escala_x2, escala_y2)
			   || uniColisaoPontoComPoligono(x2, y2, pontos1, num_pontos1, x1, y1, rot1, escala_x1, escala_y1);
	}

	return colidiu;
}

//	colisao entre poligono e sprite
bool uniColisaoPoligonoComSprite(Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, float poli_escala_x, float poli_escala_y, Sprite* spr, float x, float y, float rot, bool testar_dentro)
{
	//	se nao tiver pontos suficientes, nao testa
	if(num_pontos < 3)
		return false;

	float ax, ay;
	int larg, alt;

	spr->obterAncora(ax, ay);
	spr->obterTamanho(larg, alt);

	Vetor2D retan[4];
	retan[0].x = -ax*larg;
	retan[0].y = -ay*alt;
	retan[1].x = retan[0].x + larg;
	retan[1].y = retan[0].y;
	retan[2].x = retan[1].x;
	retan[2].y = retan[0].y + alt;
	retan[3].x = retan[0].x;
	retan[3].y = retan[2].y;

	return uniColisaoPoligonoComPoligono(pontos, num_pontos, poli_x, poli_y, poli_rot, poli_escala_x, poli_escala_y, retan, 4, x, y, rot, 1, 1, testar_dentro);
}

bool uniColisaoSpriteComSprite(Sprite* spr1, float x1, float y1, float rot1, Sprite* spr2, float x2, float y2, float rot2, bool testar_dentro)
{
	float ax1, ay1, ax2, ay2;
	int larg1, alt1, larg2, alt2;

	spr1->obterAncora(ax1, ay1);
	spr1->obterTamanho(larg1, alt1);
	spr2->obterAncora(ax2, ay2);
	spr2->obterTamanho(larg2, alt2);

	return uniColisaoRetanguloComRetangulo(x1, y1, rot1, larg1, alt1, ax1, ay1, x2, y2, rot2, larg2, alt2, ax2, ay2, testar_dentro);
}