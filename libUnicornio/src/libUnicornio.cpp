#include "libUnicornio.h"
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>

SDL_Renderer *sdl_renderer = NULL;
bool uni_init = false;
bool uni_debug = false;

double deltaTempo;
Uint64 tempoAntes;		// tempo em ticks
Uint32 maxFPS;
double framerate;

Janela janela;
int res_x; 
int res_y;

MixadorDeAudios mixador_de_audios;

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
EventosTelaDeToque telaDeToque;

bool uniInicializar(int largura_tela, int altura_tela, bool tela_cheia, string titulo_janela)
{
	//	inicializa SDL
	SDL_Init( SDL_INIT_EVERYTHING );

	//	cria janela principal
	bool janela_ok = janela.criar(largura_tela, altura_tela, tela_cheia, titulo_janela);
	if(!janela_ok)
	{
		return false;
	}
	sdl_renderer = janela.sdl_renderer;
	//	mantido para compatibilidade
	res_x = largura_tela;
	res_y = altura_tela;

	//	inicializa audio
	bool mixador_init_ok = mixador_de_audios.inicializar();
	if(!mixador_init_ok)
	{
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
        delete fonte_padrao;
		fonte_padrao = NULL;
        //  limpa as mensagens de debug, para nao tentar desenha-las sem ter uma fonte.
        for(unsigned int i = 0; i < mensagensDebug.size(); i++)
            delete mensagensDebug[i];
        mensagensDebug.clear();
	}

	//	inicializa handlers de eventos
	eventos.janela = &janela;
	eventos.aplicacao = &aplicacao;
	eventos.mouse = &mouse;
	eventos.teclado = &teclado;
	eventos.joysticks = &joysticks;
	eventos.telaDeToque = &telaDeToque;
	uniProcessarEventos();

	//	inicializa variaveis de tempo
	deltaTempo = 0;
	maxFPS = 60;	//	60 frames por segundo
	framerate = 1.0/maxFPS;
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
	mixador_de_audios.finalizar();

	//	destroi janela principal
	janela.destruir();

	//	finaliza SDL
	SDL_Quit();

	//	seta uni_init para false
	uni_init = false;
}

void uniControlarFramerate(bool sleep_loop)
{
	Uint64 framerateUs = (Uint64)(1000000.0/maxFPS);
	Uint64 tempoAtual = SDL_GetPerformanceCounter();	// tempo em counts
	Uint64 deltaTempoUs = (1000000*(tempoAtual - tempoAntes))/SDL_GetPerformanceFrequency();	//	deltaTempo em microsegundos
	
	if((deltaTempoUs < framerateUs) && (sleep_loop))
	{
		int delay = (int)framerateUs - (int)deltaTempoUs;	// delay em microsegundos
		while(delay > 0)
		{
			if(delay > 1000)
				uniDormir(1);

			deltaTempoUs = (1000000*(SDL_GetPerformanceCounter() - tempoAntes))/SDL_GetPerformanceFrequency();	//	deltaTempo em milisegundos
			delay = (int)(framerateUs - deltaTempoUs);
		}
	}

	deltaTempo = ((double)deltaTempoUs)/1000000.0;	//	deltaTempo em segundos.

	tempoAntes = tempoAtual;
}

void uniIniciarFrame(bool sleep_loop)
{
	if(!uni_init) return;

	uniControlarFramerate(sleep_loop);

	uniProcessarEventos();

	//	mantido somente para compatibilidade
	res_x = janela.getLarguraTela();
	res_y = janela.getAlturaTela();
}

void uniTerminarFrame()
{
	uniDesenharFrame();
}

unsigned int uniGetFPS()
{
	return maxFPS;
}

void uniSetFPS(unsigned int fps) 
{
	maxFPS = fps;
	framerate = 1.0/maxFPS;
}

Fonte* uniGetFontePadrao()
{
	if(uni_init)
	{
		return fonte_padrao;
	}

	return NULL;
}

void uniProcessarEventos()
{
	eventos.atualizar();
}

void processarDebug()
{
	if(!uni_debug) return;
	if(mensagensDebug.size() == 0) return;
    if(!fonte_padrao) return;

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

	if(rect.w > janela.getLarguraTela())
		rect.w = janela.getLarguraTela();

	SDL_SetRenderDrawColor(janela.sdl_renderer, 128, 128, 128, 128);
	SDL_RenderFillRect(janela.sdl_renderer, &rect);

	Texto t;
	t.setFonte(uniGetFontePadrao());

	t.setString("UNICORNIO - Painel de DEBUG");
	t.setAncora(0.5, 0.0);
	t.setCor(255, 255, 255);
	t.desenhar(rect.w/2, 0);

	t.setCor(196, 196, 196);
	int debY = 20;
	for(unsigned int i = 0; i < mensagensDebug.size(); i++)
	{
		temp = mensagensDebug[i];

		t.setAncora(0.0, 0.0);
		t.setString(temp->chave);
		t.desenhar(5, debY);

		t.setAncora(1.0, 0.0);
		t.setString(temp->valor);
		t.desenhar(rect.w - 5, debY);

		debY += 10;
	}

}

string uniGetStringDaAreaDeTransferencia()
{
	char* str = SDL_GetClipboardText();
	string s = str;
	SDL_free(str);
	return s;
}

void uniSetStringDaAreaDeTransferencia(string s)
{
	SDL_SetClipboardText(s.c_str());
}

bool uniTemStringNaAreaDeTransferencia()
{
	return SDL_HasClipboardText();
}

void uniDormir(int milisec)
{
	SDL_Delay(milisec);
}

void uniErro(string mensagem)
{
	uni_debug = true;
	ItemDebug *deb;
	deb = new ItemDebug;
	deb->chave = "ERRO";
	deb->valor = mensagem;
	mensagensDebug.push_back(deb);
}

void uniDepurar(string chave, string valor)
{
	uni_debug = true;
	ItemDebug *deb = NULL;
	ItemDebug *temp = NULL;
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

void uniDepurar(string chave, unsigned int valor)
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

void uniDesenharPixel(int x,int y, int vermelho, int verde, int azul, int opaciade)
{
	if(!uni_init) return;

	SDL_SetRenderDrawColor(janela.sdl_renderer, (Uint8)vermelho, (Uint8)verde, (Uint8)azul, (Uint8)opaciade); 
	SDL_RenderDrawPoint(janela.sdl_renderer, x, y);
}

void uniDesenharLinha(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul, int opaciade)
{
	if(!uni_init) return;

	SDL_SetRenderDrawColor(janela.sdl_renderer, (Uint8)vermelho, (Uint8)verde, (Uint8)azul, (Uint8)opaciade); 
	SDL_RenderDrawLine(janela.sdl_renderer, x1, y1, x2, y2); 
}

void uniDesenharCirculo(int x, int y, float raio, int num_segmentos, int vermelho, int verde, int azul)
{
	float c, s;

	int anterior_x = x + (int)raio;
	int anterior_y = y;

	//	desenha borda
	for(float i = 0; i <= 360; i += 360.0f/(float)num_segmentos)
	{
		c = cos(i*(float)(PI/180.0));
		s = sin(i*(float)(PI/180.0));

		int atual_x = x + (int)(c*raio);
		int atual_y = y + (int)(s*raio);

		uniDesenharLinha(anterior_x, anterior_y, atual_x, atual_y, vermelho, verde, azul);

		anterior_x = atual_x;
		anterior_y = atual_y;
	}
}

void uniDesenharRetangulo(int x, int y, float rot, int largura, int altura, float ancora_x, float ancora_y, int vermelho, int verde, int azul)
{
	float cs = cos(rot*(float)(PI/180.0));
	float sn = sin(rot*(float)(PI/180.0));

	SDL_Point pontos[4];

	pontos[0].x = (int)(-largura*ancora_x);	pontos[0].y = (int)(-altura*ancora_y);
	pontos[1].x = pontos[0].x + largura;	pontos[1].y = pontos[0].y;
	pontos[2].x = pontos[1].x;				pontos[2].y = pontos[0].y + altura;
	pontos[3].x = pontos[0].x;				pontos[3].y = pontos[2].y;

	for(int i = 0; i < 4; ++i)
	{
		//	rotaciona os pontos (em relação a origem)
		float xx = pontos[i].x * cs - pontos[i].y * sn;
		float yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos para posição
		pontos[i].x = (int)xx + x;
		pontos[i].y = (int)yy + y;
	}

	uniDesenharLinha(pontos[0].x, pontos[0].y, pontos[1].x, pontos[1].y, vermelho, verde, azul);
	uniDesenharLinha(pontos[1].x, pontos[1].y, pontos[2].x, pontos[2].y, vermelho, verde, azul);
	uniDesenharLinha(pontos[2].x, pontos[2].y, pontos[3].x, pontos[3].y, vermelho, verde, azul);
	uniDesenharLinha(pontos[3].x, pontos[3].y, pontos[0].x, pontos[0].y, vermelho, verde, azul);
}

void uniDesenharPoligono(int x, int y, float rot, Vetor2D* pontos, int num_pontos, int vermelho, int verde, int azul)
{
	if(num_pontos < 3)
		return;

	float cs = cos(rot*(float)(PI/180.0));
	float sn = sin(rot*(float)(PI/180.0));

	float xx = pontos[0].x * cs - pontos[0].y * sn;
	float yy = pontos[0].x * sn + pontos[0].y * cs;

	int x_anterior = (int)xx + x;
	int y_anterior = (int)yy + y;

	int primeiro_x = x_anterior;
	int primeiro_y = y_anterior;

	for(int i = 1; i < num_pontos; ++i)
	{
		//	rotaciona os pontos (em relação a origem)
		xx = pontos[i].x * cs - pontos[i].y * sn;
		yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos para posição
		int x_atual = (int)xx + x;
		int y_atual = (int)yy + y;

		uniDesenharLinha(x_anterior, y_anterior, x_atual, y_atual, vermelho, verde, azul);

		x_anterior = x_atual;
		y_anterior = y_atual;
	}

	uniDesenharLinha(x_anterior, y_anterior, primeiro_x, primeiro_y, vermelho, verde, azul);
}

void uniDesenharTexto(string txt, int x, int y, int cR, int cG, int cB, float ancora_x, float ancora_y)
{
	if(!uni_init) return;
    if(!fonte_padrao) return;

	Texto t;
	t.setFonte(fonte_padrao);
	t.setString(txt);
	t.setCor(cR, cG, cB);

	t.setAncora(ancora_x, ancora_y);

	t.desenhar(x, y);
}

void uniDesenharFrame(bool limpar)
{
	if(!uni_init) return;

	processarDebug();
	janela.desenhar();
	
	if(limpar) 
		janela.limpar();
}