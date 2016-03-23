#ifndef UNI_SPRITE_H
#define UNI_SPRITE_H

#include "SpriteSheet.h"
#include "Vetor2D.h"
#include "Cor.h"

class Sprite
{	
public:
	Sprite();
	Sprite(const Sprite &cp);
	~Sprite();

	Sprite& operator=(const Sprite &r);
	bool operator==(const Sprite &r);
	bool operator!=(const Sprite &r);

	Vetor2D getAncora();
	float getAncoraX();
	float getAncoraY();
	Vetor2D getEscala();
	float getEscalaX();
	float getEscalaY();
	int	getLargura();			//	escalado
	int getAltura();			//	escalado
	int	getLarguraOriginal();	//	não escalado
	int getAlturaOriginal();	//	não escalado
	int getAnimacao();
	int getFrame();
	float getVelocidadeAnimacao();
	bool getPause();
	bool getInverterX();
	bool getInverterY();
	Cor getCor();
	int getCorVermelho();
	int getCorVerde();
	int getCorAzul();
	int getCorAlpha();
	SpriteSheet *getSpriteSheet();

	void obterAncora(float &ax, float &ay);
	void obterEscala(float &ex, float& ey);
	void obterTamanho(int &larg, int &alt);			//	escalado
	void obterTamanhoOriginal(int &larg, int &alt);	//	não escalado
	void obterCor(int &r, int &g, int &b);
	void obterCor(int &r, int &g, int &b, int &a);

	bool terminouAnimacao();

	void setAncora(Vetor2D anc);
	void setAncora(float x, float y);
	void setEscala(Vetor2D esc);
	void setEscala(float ex, float ey);
	void setAnimacao(int anim, bool recomecar = false);
	void setFrame(int frame);
	void setVelocidadeAnimacao(float vel);
	void setPause(bool p);
	void setInverterX(bool b);
	void setInverterY(bool b);
	void setCor(Cor cor);
	void setCor(int r, int g, int b);
	void setCor(int r, int g, int b, int a);
	void setCorVermelho(int vermelho);
	void setCorVerde(int verde);
	void setCorAzul(int azul);
	void setCorAlpha(int alpha);
	void setAnimacaoAoContrario(bool b);
	void setSpriteSheet(string nome);
	void setSpriteSheet(SpriteSheet *sheet);

	void recomecarAnimacao();
	void avancarAnimacao();
	void avancarAnimacao(double dt);
	bool desenhar(int x, int y, float rot = 0.0f);

protected:
	SpriteSheet *sheet;
	Uint8 frame_atual;
	Uint8 anim_atual;
	double tempo_anim;
	float vel_anim;
	Vetor2D escala;
	Vetor2D ancora;
	Uint8 flip_mode;
	bool animacao_ao_contrario;
	bool pause;
	bool terminou_anim;
	SDL_Color cor;
};

#endif