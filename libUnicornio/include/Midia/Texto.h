#ifndef UNI_TEXTO_H
#define UNI_TEXTO_H

#include "Fonte.h"

class Texto
{
private:
	Fonte* fonte;
	SDL_Texture* tex;
	SDL_Texture* tex_borda;

	SDL_Rect rect;
	int rect_borda_larg;
	int rect_borda_alt;
	SDL_Color cor;
	SDL_Color cor_borda;
	int tamanho_borda;
	float ancora_x;
	float ancora_y;
	float escala_x;
	float escala_y;
	string str;

	void criarTextura();
	void criarTexturaBorda();

public:
	Texto();
	~Texto();

	float getAncoraX();
	float getAncoraY();
	float getEscalaX();
	float getEscalaY();
	int	getLargura();			//	escalado
	int getAltura();			//	escalado
	int	getLarguraOriginal();	//	não escalado
	int getAlturaOriginal();	//	não escalado
	int getCorVermelho();
	int getCorVerde();
	int getCorAzul();
	int getCorAlpha();
	int getCorBordaVermelho();
	int getCorBordaVerde();
	int getCorBordaAzul();
	int getCorBordaAlpha();
	int getTamanhoBorda();
	Fonte* getFonte();

	string getTexto();

	void obterAncora(float &x, float &y);
	void obterEscala(float &sx, float& sy);
	void obterTamanho(int &w, int &h);			//	escalado
	void obterTamanhoOriginal(int &w, int &h);	//	não escalado
	void obterCor(int &vermelho, int &verde, int &azul);
	void obterCor(int &vermelho, int &verde, int &azul, int &alpha);
	void obterCorBorda(int &vermelho, int &verde, int &azul);
	void obterCorBorda(int &vermelho, int &verde, int &azul, int &alpha);

	void setAncora(float x, float y);
	void setEscala(float sx, float sy);
	void setCor(int vermelho = 255, int verde = 255, int azul = 255, int alpha = 255);
	void setCorVermelho(int vermelho);
	void setCorVerde(int verde);
	void setCorAzul(int azul);
	void setCorAlpha(int alpha);
	void setCorBorda(int vermelho = 255, int verde = 255, int azul = 255, int alpha = 255);
	void setCorBordaVermelho(int vermelho);
	void setCorBordaVerde(int verde);
	void setCorBordaAzul(int azul);
	void setCorBordaAlpha(int alpha);
	void setFonte(Fonte* fnt);
	void setTamanhoBorda(int tamanho);

	void setTexto(string txt);

	void desenhar(int x, int y, float rot = 0);
	void apagar();
};

#endif