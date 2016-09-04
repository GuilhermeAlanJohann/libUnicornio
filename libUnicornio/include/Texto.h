#ifndef UNI_TEXTO_H
#define UNI_TEXTO_H

#include "uniAPI.h"
#include "Fonte.h"
#include "Vetor2D.h"

enum UNI_API EnumAlinhamentoTexto
{
	TEXTO_ALINHADO_A_ESQUERDA,
	TEXTO_ALINHADO_A_DIREITA,
	TEXTO_CENTRALIZADO //TEXTO_ALINHADO_AO_CENTRO
};

struct UNI_API Letra
{
	Glifo* glifo;
	Cor cor;
	bool fimDeLinha;	//	uso interno. Não mudar.
};

class UNI_API Texto
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
	int	getLarguraOriginal();	//	nao escalado
	int	getAlturaOriginal();	//	nao escalado
	int getLarguraMaxima();
	Cor getCor();
	int	getCorVermelho();
	int	getCorVerde();
	int	getCorAzul();
	int	getCorAlpha();

	int	getNumLinhas();
	float getEspacamentoLinhas();
	EnumAlinhamentoTexto getAlinhamento();
	Fonte *getFonte();

	string getString();
	wstring getWstring();

	Letra* getLetra(unsigned int indice);
	Cor getCorLetra(unsigned int indice);

	void obterAncora(float &x, float &y);
	void obterEscala(float &sx, float& sy);
	void obterTamanho(int &larg, int &alt);				//	escalado
	void obterTamanhoOriginal(int &larg, int &alt);		//	nao escalado
	void obterCor(int &r, int &g, int &b);
	void obterCor(int &r, int &g, int &b, int &a);

	void setAncora(Vetor2D anc);
	void setAncora(float x, float y);
	void setEscala(Vetor2D esc);
	void setEscala(float sx, float sy);
	void setEscalaX(float x);
	void setEscalaY(float y);
	void setLarguraMaxima(int larg_max);
	void setCor(Cor cor, bool aplicarEmTodasAsLetras = false);
	void setCor(int r, int g, int b, bool aplicarEmTodasAsLetras = false);
	void setCor(int r, int g, int b, int a, bool aplicarEmTodasAsLetras = false);
	void setCorVermelho(int vermelho, bool aplicarEmTodasAsLetras = false);
	void setCorVerde(int verde, bool aplicarEmTodasAsLetras = false);
	void setCorAzul(int azul, bool aplicarEmTodasAsLetras = false);
	void setCorAlpha(int alpha, bool aplicarEmTodasAsLetras = false);
	void setEspacamentoLinhas(float espacamento);
	void setAlinhamento(EnumAlinhamentoTexto alinhamento);
	void setFonte(string nome);
	void setFonte(Fonte *fnt);

	void setString(string str);
	void setWstring(wstring wstr_);

	void setCorLetra(unsigned int i, Cor cor);
	void setCorLetra(unsigned int i, int r, int g, int b, int a = 255);
	void setCorPalavra(const string& palavra, Cor cor);
	void setCorPalavra(const string& palavra, int r, int g, int b, int a = 255);

	void adicionarString(string str, bool noInicio = false);
	void adicionarWstring(wstring wstr_, bool noInicio = false);

	void removerString(string str);
	void removerWstring(wstring wstr_);

	void apagar();
	bool quebrarStringParaLargura(int larg);

	void desenhar(int x, int y, float rot = 0.0f);

protected:
	wstring converterParaWstring(const string& s);
	wstring getWstringParaLarguraMaxima(int larg_max, int& rLarg, int& rAlt, int& rNumLinhas);

	void criarVetorDeLetras();
	void adicionarAoVetorDeLetras(string str, bool noInicio);
	void adicionarAoVetorDeLetras(wstring wstr_, bool noInicio);
	void removerDoVetorDeLetras(unsigned int inicio, unsigned int fim);
	void calcularDimensoes();

	Fonte *fonte;

	int largura;
	int altura;
	Vetor2D ancora;
	Vetor2D escala;

	int largura_max;

	wstring wstr;
	int num_linhas;
	float espacamento_linhas;
	EnumAlinhamentoTexto alinhamento;

	Cor cor;

	vector<Letra> letras;
};

#endif