#include "Texto.h"
#include "libUnicornio.h"

Texto::Texto()
{
	tex = NULL;
	fonte = NULL;
	texCima = NULL;
	fonteCima = NULL;
	ancora_x = 0.5;
	ancora_y = 0.5;
	escala_x = 1.0;
	escala_y = 1.0;
	cor.r = 255;
	cor.g = 255;
	cor.b = 255;
	cor.a = 255;
	corCima.r = 255;
	corCima.g = 255;
	corCima.b = 255;
	corCima.a = 255;
}

Texto::~Texto()
{
	if(tex)
	{
		SDL_DestroyTexture(tex);
	}
}

float Texto::getAncoraX()
{
	return ancora_x;
}

float Texto::getAncoraY()
{
	return ancora_y;
}

float Texto::getEscalaX()
{
	return escala_x;
}

float Texto::getEscalaY()
{
	return escala_y;
}

int	Texto::getLargura()
{
	return rect.w*escala_x;
}

int Texto::getAltura()
{
	return rect.h*escala_y;
}

int	Texto::getLarguraOriginal()
{
	return rect.w;
}

int Texto::getAlturaOriginal()
{
	return rect.h;
}

int Texto::getCorVermelho()
{
	return cor.r;
}

int Texto::getCorVerde()
{
	return cor.g;
}

int Texto::getCorAzul()
{
	return cor.b;
}

int Texto::getCorAlpha()
{
	return cor.a;
}

int Texto::getCorCimaVermelho()
{
	return corCima.r;
}

int Texto::getCorCimaVerde()
{
	return corCima.g;
}

int Texto::getCorCimaAzul()
{
	return corCima.b;
}

int Texto::getCorCimaAlpha()
{
	return corCima.a;
}

Fonte* Texto::getFonte()
{
	return fonte;
}

Fonte* Texto::getFonteCima()
{
	return fonteCima;
}

string Texto::getTexto()
{
	return str;
}

void Texto::obterAncora(float &x, float &y)
{
	x = ancora_x;
	y = ancora_y;
}

void Texto::obterEscala(float &sx, float& sy)
{
	sx = escala_x;
	sy = escala_y;
}

void Texto::obterTamanho(int &w, int &h)
{
	w = getLargura();
	h = getAltura();
}

void Texto::obterTamanhoOriginal(int &w, int &h)
{
	w = getLarguraOriginal();
	h = getAlturaOriginal();
}

void Texto::obterCor(int &vermelho, int &verde, int &azul)
{
	vermelho = cor.r;
	verde = cor.g;
	azul = cor.b;
}

void Texto::obterCor(int &vermelho, int &verde, int &azul, int &alpha)
{
	vermelho = cor.r;
	verde = cor.g;
	azul = cor.b;
	alpha = cor.a;
}

void Texto::obterCorCima(int &vermelho, int &verde, int &azul)
{
	vermelho = corCima.r;
	verde = corCima.g;
	azul = corCima.b;
}

void Texto::obterCorCima(int &vermelho, int &verde, int &azul, int &alpha)
{
	vermelho = corCima.r;
	verde = corCima.g;
	azul = corCima.b;
	alpha = corCima.a;
}

void Texto::setAncora(float x, float y)
{
	ancora_x = x;
	ancora_y = y;
}

void Texto::setEscala(float sx, float sy)
{
	escala_x = sx;
	escala_y = sy;
}

void Texto::setCor(int vermelho, int verde, int azul, int alpha)
{
	cor.r = vermelho;
	cor.g = verde;
	cor.b = azul;
	cor.a = alpha;
}

void Texto::setCorVermelho(int vermelho)
{
	cor.r = vermelho;
}

void Texto::setCorVerde(int verde)
{
	cor.g = verde;
}

void Texto::setCorAzul(int azul)
{
	cor.b = azul;
}

void Texto::setCorAlpha(int alpha)
{
	cor.a = alpha;
}

void Texto::setCorCima(int vermelho, int verde, int azul, int alpha)
{
	corCima.r = vermelho;
	corCima.g = verde;
	corCima.b = azul;
	corCima.a = alpha;
}

void Texto::setCorCimaVermelho(int vermelho)
{
	corCima.r = vermelho;
}

void Texto::setCorCimaVerde(int verde)
{
	corCima.g = verde;
}

void Texto::setCorCimaAzul(int azul)
{
	corCima.b = azul;
}

void Texto::setCorCimaAlpha(int alpha)
{
	corCima.a = alpha;
}

void Texto::setFonte(Fonte* fnt)
{
	fonte = fnt;
}

void Texto::setFonteCima(Fonte* fnt)
{
	fonteCima = fnt;
}

void Texto::setTexto(string txt)
{
	if(!uni_init)
		return;

	str = txt;

	//	Texto de baixo (padrão)
	if(!fonte) 
		return;

	if(tex)
		SDL_DestroyTexture(tex);

	SDL_Color color = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Blended(fonte->getTTF_Font(), str.c_str(), color); 
	tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
    SDL_FreeSurface(surface);

	//	Texto de cima
	if(!fonteCima) 
		return;

	if(texCima)
		SDL_DestroyTexture(texCima);

	SDL_Surface *surfaceCima = TTF_RenderText_Blended(fonteCima->getTTF_Font(), str.c_str(), color); 
	texCima = SDL_CreateTextureFromSurface(renderer, surfaceCima);
	SDL_QueryTexture(texCima, NULL, NULL, &rect.w, &rect.h);
    SDL_FreeSurface(surfaceCima);
}

void Texto::desenhar(int x, int y, float rot)
{
	if(!uni_init) 
		return;

	//	Fonte de baixo (padrão)
	if(!fonte) 
	{
		uniDesenharTexto("Nao pode desenhar Texto antes de setar Fonte.",x,y,255,0,0);
		return;
	}

	SDL_Rect retangulo;
	retangulo.w = rect.w*escala_x;
	retangulo.h = rect.h*escala_y;

	SDL_Point pivot = {rect.w * ancora_x, rect.h * ancora_y};

	retangulo.x = x - pivot.x;
	retangulo.y = y - pivot.y;
    
	// seta cor
	SDL_SetTextureColorMod(tex, cor.r, cor.g, cor.b);
	SDL_SetTextureAlphaMod(tex, cor.a);

    SDL_RenderCopyEx(renderer, tex, NULL, &retangulo, rot, &pivot, SDL_FLIP_NONE);

	//	Fonte de cima
	if(!fonteCima) 
		return;

	// seta cor
	SDL_SetTextureColorMod(texCima, corCima.r, corCima.g, corCima.b);
	SDL_SetTextureAlphaMod(texCima, corCima.a);

    SDL_RenderCopyEx(renderer, texCima, NULL, &retangulo, rot, &pivot, SDL_FLIP_NONE);
}