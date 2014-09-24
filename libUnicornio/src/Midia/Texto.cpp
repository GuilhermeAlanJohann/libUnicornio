#include "Texto.h"
#include "libUnicornio.h"

Texto::Texto()
{
	tex = NULL;
	tex_borda = NULL;
	fonte = NULL;
	ancora_x = 0.5;
	ancora_y = 0.5;
	escala_x = 1.0;
	escala_y = 1.0;
	cor.r = 255;
	cor.g = 255;
	cor.b = 255;
	cor.a = 255;
	cor_borda.r = 0;
	cor_borda.g = 0;
	cor_borda.b = 0;
	cor_borda.a = 255;
	tamanho_borda = 0;
}

Texto::~Texto()
{
	apagar();
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

int Texto::getCorBordaVermelho()
{
	return cor_borda.r;
}

int Texto::getCorBordaVerde()
{
	return cor_borda.g;
}

int Texto::getCorBordaAzul()
{
	return cor_borda.b;
}

int Texto::getCorBordaAlpha()
{
	return cor_borda.a;
}

int Texto::getTamanhoBorda()
{
	return tamanho_borda;
}

Fonte* Texto::getFonte()
{
	return fonte;
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

void Texto::obterCorBorda(int &vermelho, int &verde, int &azul)
{
	vermelho = cor_borda.r;
	verde = cor_borda.g;
	azul = cor_borda.b;
}

void Texto::obterCorBorda(int &vermelho, int &verde, int &azul, int &alpha)
{
	vermelho = cor_borda.r;
	verde = cor_borda.g;
	azul = cor_borda.b;
	alpha = cor_borda.a;
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

void Texto::setCorBorda(int vermelho, int verde, int azul, int alpha)
{
	cor_borda.r = vermelho;
	cor_borda.g = verde;
	cor_borda.b = azul;
	cor_borda.a = alpha;
}

void Texto::setCorBordaVermelho(int vermelho)
{
	cor_borda.r = vermelho;
}

void Texto::setCorBordaVerde(int verde)
{
	cor_borda.g = verde;
}

void Texto::setCorBordaAzul(int azul)
{
	cor_borda.b = azul;
}

void Texto::setCorBordaAlpha(int alpha)
{
	cor_borda.a = alpha;
}

void Texto::setTamanhoBorda(int tamanho)
{
	tamanho_borda = tamanho;

	if(fonte)
		criarTexturaBorda();
}

void Texto::setFonte(string nome)
{
	setFonte(recursos.getFonte(nome));
}

void Texto::setFonte(Fonte* fnt)
{
	if(!fnt)
	{
		return;
	}

	if(fonte == fnt)
	{
		return;
	}

	fonte = fnt;
}

void Texto::setTexto(string txt)
{
	if(!uni_init)
		return;

	str = txt;

	if(!fonte) 
	{
		uniErro("Nao pode setar Texto antes de setar Fonte.");
		return;
	}

	if(str == "")
	{
		apagar();
	}
	else
	{
		criarTextura();
		criarTexturaBorda();
	}
}

void Texto::desenhar(int x, int y, float rot)
{
	if(!uni_init) 
		return;

	if(!fonte) 
	{
		uniDesenharTexto("Nao pode desenhar Texto antes de setar Fonte.",x,y,255,0,0);
		return;
	}

	SDL_Rect retangulo;
	retangulo.w = rect.w*escala_x;
	retangulo.h = rect.h*escala_y;

	SDL_Point pivot = {retangulo.w * ancora_x, retangulo.h * ancora_y};

	retangulo.x = x - pivot.x;
	retangulo.y = y - pivot.y;
    
	// seta cor
	SDL_SetTextureColorMod(tex, cor.r, cor.g, cor.b);
	SDL_SetTextureAlphaMod(tex, cor.a);

    SDL_RenderCopyEx(renderer, tex, NULL, &retangulo, rot, &pivot, SDL_FLIP_NONE);

	//	desenhar borda
	if(tex_borda)
	{
		retangulo.w = rect_borda_larg*escala_x;
		retangulo.h = rect_borda_alt*escala_y;

		pivot.x = retangulo.w * ancora_x;
		pivot.y = retangulo.h * ancora_y;

		retangulo.x = x - (int)(retangulo.w*ancora_x) - (tamanho_borda*2)*escala_x*(0.5f - ancora_x);
		retangulo.y -= (tamanho_borda*2)*escala_y*ancora_y;

		SDL_SetTextureColorMod(tex_borda, cor_borda.r, cor_borda.g, cor_borda.b);
		SDL_SetTextureAlphaMod(tex_borda, cor_borda.a);

		SDL_RenderCopyEx(renderer, tex_borda, NULL, &retangulo, rot, &pivot, SDL_FLIP_NONE);
	}
}

void Texto::apagar()
{
	if(tex)
	{
		SDL_DestroyTexture(tex);
		tex = NULL;
	}

	if(tex_borda)
	{
		SDL_DestroyTexture(tex_borda);
		tex_borda = NULL;
	}

	str = "";

}

void Texto::criarTextura()
{
	if(tex)
		SDL_DestroyTexture(tex);

	SDL_Color color = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Blended(fonte->getTTF_Font(), str.c_str(), color); 
	tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
    SDL_FreeSurface(surface);
}

void Texto::criarTexturaBorda()
{
	if(tamanho_borda <= 0)
		return;

	if(tex_borda)
		SDL_DestroyTexture(tex_borda);

	TTF_Font* font = fonte->getTTF_Font();
	TTF_SetFontOutline(font, tamanho_borda);

	SDL_Color color = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Blended(font, str.c_str(), color); 
	tex_borda = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(tex_borda, NULL, NULL, &rect_borda_larg, &rect_borda_alt);
    SDL_FreeSurface(surface);

	TTF_SetFontOutline(font, 0);
}