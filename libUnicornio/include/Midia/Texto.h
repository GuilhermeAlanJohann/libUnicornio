#ifndef UNI_TEXTO_H
#define UNI_TEXTO_H

#include "Fonte.h"
#include "Vetor2D.h"

enum TipoAlinhamentoTexto
{
	TEXTO_ALINHADO_A_ESQUERDA,
	TEXTO_ALINHADO_A_DIREITA,
	TEXTO_CENTRALIZADO
};

class Texto
{
public:
	Texto();
	~Texto();

	Vetor2D getAncora();
	float getAncoraX();
	float getAncoraY();
	Vetor2D getEscala();
	float getEscalaX();
	float getEscalaY();
	int	getLargura();			//	escalado
	int	getAltura();			//	escalado
	int	getLarguraOriginal();	//	não escalado
	int	getAlturaOriginal();	//	não escalado
	int	getLarguraLinha(int linha);				//	escalado
	int	getAlturaLinha(int linha);				//	escalado
	int	getLarguraOriginalLinha(int linha);		//	não escalado	
	int	getAlturaOriginalLinha(int linha);		//	não escalado	
	int	getCorVermelho();
	int	getCorVerde();
	int	getCorAzul();
	int	getCorAlpha();

	int	getNumLinhas();
	float getEspacamentoLinhas();
	TipoAlinhamentoTexto getAlinhamento();
	Fonte *getFonte();

	string getString();
	string getStringLinha(int linha);
	wstring getWstring();
	wstring getWstringLinha(int linha);

	void obterAncora(float &x, float &y);
	void obterEscala(float &sx, float& sy);
	void obterTamanho(int &larg, int &alt);							//	escalado
	void obterTamanhoOriginal(int &larg, int &alt);					//	não escalado
	void obterTamanhoLinha(int linha, int &larg, int &alt);			//	escalado		
	void obterTamanhoOriginalLinha(int linha, int &larg, int &alt);	//	não escalado	
	void obterCor(int &vermelho, int &verde, int &azul);
	void obterCor(int &vermelho, int &verde, int &azul, int &alpha);

	void setAncora(Vetor2D anc);
	void setAncora(float x, float y);
	void setEscala(Vetor2D esc);
	void setEscala(float sx, float sy);
	void setCor(int vermelho = 255, int verde = 255, int azul = 255, int alpha = 255);
	void setCorVermelho(int vermelho);
	void setCorVerde(int verde);
	void setCorAzul(int azul);
	void setCorAlpha(int alpha);
	void setEspacamentoLinhas(float espacamento);
	void setAlinhamento(TipoAlinhamentoTexto alinhamento);
	void setFonte(string nome);		
	void setFonte(Fonte *fnt);	

	void setString(string str);
	void setStringLinha(string str, int linha);
	void setWstring(wstring wstr_);
	void setWstringLinha(wstring wstr_, int linha);

	void adicionarString(string str);
	void adicionarStringNaLinha(string str, int linha);
	void adicionarWstring(wstring wstr_);
	void adicionarWstringNaLinha(wstring wstr_, int linha);
	
	void removerString(string str);
	void removerStringNaLinha(string str, int linha);
	void removerWstring(wstring wstr_);
	void removerWstringNaLinha(wstring wstr_, int linha);
	void removerLinha(int linha);

	void apagar();

	void desenhar(int x, int y);
	void desenhar(int x, int y, float rot);

private:
	string converterParaString(wstring &s);
	wstring converterParaWstring(string &s);

	unsigned int getSomaDosAvancos(unsigned int inicio, unsigned int fim);
	void desenharCaractere(wchar_t caractere, int x_canto_glifo, int y_canto_glifo, int x_texto, int y_texto);
	void desenharCaractere(wchar_t caractere, int x_canto_glifo, int y_canto_glifo, int x_texto, int y_texto, float rot_texto);
	void calcularTamanho();

	Fonte *fonte;

	int largura;
	int altura;
	Vetor2D ancora;
	Vetor2D escala;

	wstring wstr;
	int num_linhas;
	float espacamento_linhas;
	TipoAlinhamentoTexto alinhamento;

	SDL_Color cor;
};

#endif