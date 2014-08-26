#ifndef UNI_TEXTO_H
#define UNI_TEXTO_H

#include "Fonte.h"

class Texto
{
private:
	SDL_Rect rect;
	SDL_Texture* tex;
	Fonte* fonte;
	SDL_Color cor;
	SDL_Texture* texCima;
	Fonte* fonteCima;
	SDL_Color corCima;
	float ancora_x;
	float ancora_y;
	float escala_x;
	float escala_y;
	string str;

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
	int getCorCimaVermelho();
	int getCorCimaVerde();
	int getCorCimaAzul();
	int getCorCimaAlpha();
	Fonte* getFonte();
	Fonte* getFonteCima();

	string getTexto();

	void obterAncora(float &x, float &y);
	void obterEscala(float &sx, float& sy);
	void obterTamanho(int &w, int &h);			//	escalado
	void obterTamanhoOriginal(int &w, int &h);	//	não escalado
	void obterCor(int &vermelho, int &verde, int &azul);
	void obterCor(int &vermelho, int &verde, int &azul, int &alpha);
	void obterCorCima(int &vermelho, int &verde, int &azul);
	void obterCorCima(int &vermelho, int &verde, int &azul, int &alpha);

	void setAncora(float x, float y);
	void setEscala(float sx, float sy);
	void setCor(int vermelho = 255, int verde = 255, int azul = 255, int alpha = 255);
	void setCorVermelho(int vermelho);
	void setCorVerde(int verde);
	void setCorAzul(int azul);
	void setCorAlpha(int alpha);
	void setCorCima(int vermelho = 255, int verde = 255, int azul = 255, int alpha = 255);
	void setCorCimaVermelho(int vermelho);
	void setCorCimaVerde(int verde);
	void setCorCimaAzul(int azul);
	void setCorCimaAlpha(int alpha);
	void setFonte(Fonte* fnt);
	void setFonteCima(Fonte* fnt);

	void setTexto(string txt);

	void desenhar(int x, int y, float rot = 0);
};

#endif