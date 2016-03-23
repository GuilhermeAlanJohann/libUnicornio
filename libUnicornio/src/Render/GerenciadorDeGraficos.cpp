#include "GerenciadorDeGraficos.h"
#include "uniFuncoesPrincipais.h"
#include "Global.h"
#include "Texto.h"

GerenciadorDeGraficos::GerenciadorDeGraficos()
{
	fontePadrao = NULL;
	sdl_textureBranco = NULL;
}

GerenciadorDeGraficos::~GerenciadorDeGraficos()
{
}

void GerenciadorDeGraficos::inicializar()
{
	carregarFontePadrao();
	criarSDL_TextureBranco();
}

void GerenciadorDeGraficos::finalizar()
{
	destruirSDL_TextureBranco();
	descarregarFontePadrao();
}

void GerenciadorDeGraficos::desenharPixel(int x, int y, int vermelho, int verde, int azul, int alpha)
{
	SDL_SetRenderDrawColor(gJanela.sdl_renderer, (Uint8)vermelho, (Uint8)verde, (Uint8)azul, (Uint8)alpha);
	SDL_RenderDrawPoint(gJanela.sdl_renderer, x, y);
}

void GerenciadorDeGraficos::desenharLinha(int x1, int y1, int x2, int y2, int vermelho, int verde, int azul, int alpha)
{
	SDL_SetRenderDrawColor(gJanela.sdl_renderer, (Uint8)vermelho, (Uint8)verde, (Uint8)azul, (Uint8)alpha);
	SDL_RenderDrawLine(gJanela.sdl_renderer, x1, y1, x2, y2);
}

void GerenciadorDeGraficos::desenharCirculo(int x, int y, float raio, int num_segmentos, int vermelho, int verde, int azul)
{
	float c, s;

	int anterior_x = x + (int)raio;
	int anterior_y = y;

	SDL_SetRenderDrawColor(gJanela.sdl_renderer, (Uint8)vermelho, (Uint8)verde, (Uint8)azul, 255);

	float inc = 360.0f / (float)num_segmentos;

	for (float i = inc; i < 360.0f; i += inc)
	{
		c = cos(i*(float)(PI / 180.0));
		s = sin(i*(float)(PI / 180.0));

		int atual_x = x + (int)(c*raio);
		int atual_y = y + (int)(s*raio);

		SDL_RenderDrawLine(gJanela.sdl_renderer, anterior_x, anterior_y, atual_x, atual_y);

		anterior_x = atual_x;
		anterior_y = atual_y;
	}

	SDL_RenderDrawLine(gJanela.sdl_renderer, anterior_x, anterior_y, x + (int)raio, y);
}

void GerenciadorDeGraficos::desenharRetangulo(const Retangulo& retangulo, int vermelho, int verde, int azul)
{
	SDL_SetRenderDrawColor(gJanela.sdl_renderer, vermelho, verde, azul, 255);
	SDL_Rect rect = retangulo.getSDL_Rect();
	SDL_RenderDrawRect(gJanela.sdl_renderer, &rect);
}

void GerenciadorDeGraficos::desenharRetangulo(int x, int y, float rot, int largura, int altura, float ancora_x, float ancora_y, int vermelho, int verde, int azul)
{
	float cs = cos(rot*(float)(PI / 180.0));
	float sn = sin(rot*(float)(PI / 180.0));

	//	Desconta um pixel na largura e altura, pois se nao
	//	eles ficariam sobrando na direita e em baixo
	SDL_Point pontos[4];
	pontos[0].x = (int)(-largura*ancora_x);	pontos[0].y = (int)(-altura*ancora_y);
	pontos[1].x = pontos[0].x + largura -1;	pontos[1].y = pontos[0].y;
	pontos[2].x = pontos[1].x;				pontos[2].y = pontos[0].y + altura - 1;
	pontos[3].x = pontos[0].x;				pontos[3].y = pontos[2].y;

	for (int i = 0; i < 4; ++i)
	{
		//	rotaciona os pontos (em relação a origem)
		float xx = pontos[i].x * cs - pontos[i].y * sn;
		float yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos para posição
		pontos[i].x = (int)xx + x;
		pontos[i].y = (int)yy + y;
	}

	desenharLinha(pontos[0].x, pontos[0].y, pontos[1].x, pontos[1].y, vermelho, verde, azul);
	desenharLinha(pontos[1].x, pontos[1].y, pontos[2].x, pontos[2].y, vermelho, verde, azul);
	desenharLinha(pontos[2].x, pontos[2].y, pontos[3].x, pontos[3].y, vermelho, verde, azul);
	desenharLinha(pontos[3].x, pontos[3].y, pontos[0].x, pontos[0].y, vermelho, verde, azul);
}

void GerenciadorDeGraficos::desenharPoligono(int x, int y, float rot, Vetor2D* pontos, int num_pontos, int vermelho, int verde, int azul)
{
	if (num_pontos < 3)
		return;

	float cs = cos(rot*(float)(PI / 180.0));
	float sn = sin(rot*(float)(PI / 180.0));

	float xx = pontos[0].x * cs - pontos[0].y * sn;
	float yy = pontos[0].x * sn + pontos[0].y * cs;

	int x_anterior = (int)xx + x;
	int y_anterior = (int)yy + y;

	int primeiro_x = x_anterior;
	int primeiro_y = y_anterior;

	for (int i = 1; i < num_pontos; ++i)
	{
		//	rotaciona os pontos (em relação a origem)
		xx = pontos[i].x * cs - pontos[i].y * sn;
		yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos para posição
		int x_atual = (int)xx + x;
		int y_atual = (int)yy + y;

		desenharLinha(x_anterior, y_anterior, x_atual, y_atual, vermelho, verde, azul);

		x_anterior = x_atual;
		y_anterior = y_atual;
	}

	desenharLinha(x_anterior, y_anterior, primeiro_x, primeiro_y, vermelho, verde, azul);
}

void GerenciadorDeGraficos::desenharTexto(string txt, int x, int y, int vermelho, int verde, int azul, int alpha, float ancora_x, float ancora_y)
{
	if (!fontePadrao) 
		return;

	Texto t;
	t.setFonte(fontePadrao);
	t.setString(txt);
	t.setCor(vermelho, verde, azul, alpha, true);

	t.setAncora(ancora_x, ancora_y);

	t.desenhar(x, y);
}

void GerenciadorDeGraficos::desenharSDL_Texture(SDL_Texture* texture, const Retangulo& recorte, const Vetor2D& escala, const Vetor2D& ancora, const Vetor2D& pos, float rot, SDL_RendererFlip flip_mode, const Cor& cor)
{
	SDL_Rect src = recorte.getSDL_Rect();
	SDL_Rect dest = {(int)pos.x, (int)pos.y, (int)(src.w*escala.x), (int)(src.h*escala.y) };
	dest.x -= dest.w*ancora.x;
	dest.y -= dest.h*ancora.y;

	SDL_Point center = { (int)(dest.w * ancora.x), (int)(dest.h * ancora.y) };
	dest.x -= center.x;
	dest.y -= center.y;

	SDL_SetTextureColorMod(texture, cor.r, cor.g, cor.b);
	SDL_SetTextureAlphaMod(texture, cor.a);
	SDL_RenderCopyEx(gJanela.sdl_renderer, texture, &src, &dest, rot, &center, flip_mode);
}

Fonte* GerenciadorDeGraficos::getFontePadrao()
{
	return fontePadrao;
}

SDL_Texture* GerenciadorDeGraficos::getSDL_TextureBranco()
{
	return sdl_textureBranco;
}

void GerenciadorDeGraficos::carregarFontePadrao()
{
	fontePadrao = new Fonte;
	if (fontePadrao->carregar("fonte_padrao.ttf", 10) == false)
	{
		delete fontePadrao;
		fontePadrao = NULL;
	}
}

void GerenciadorDeGraficos::descarregarFontePadrao()
{
	if (fontePadrao)
	{
		fontePadrao->descarregar();
		delete fontePadrao;
		fontePadrao = NULL;
	}
}

void GerenciadorDeGraficos::criarSDL_TextureBranco()
{
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	SDL_Surface* surface = SDL_CreateRGBSurface(0, 8, 8, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 255, 255, 255));

	sdl_textureBranco = SDL_CreateTextureFromSurface(gJanela.sdl_renderer, surface);
	SDL_SetTextureBlendMode(sdl_textureBranco, SDL_BLENDMODE_BLEND);

	SDL_FreeSurface(surface);
}

void GerenciadorDeGraficos::destruirSDL_TextureBranco()
{
	SDL_DestroyTexture(sdl_textureBranco);
	sdl_textureBranco = NULL;
}
