#ifndef UNI_PAINELDEDEBUG_H
#define UNI_PAINELDEDEBUG_H

#include "uniAPI.h"
#include <vector>
#include <string>
#include "Quad.h"
#include "Cor.h"
#include "Vetor2D.h"

using namespace std;

struct ItemDebug
{
	void* ptr;
	string chave;
	string valor;
	Cor cor;
};

class UNI_API PainelDeDebug
{
public:
	PainelDeDebug();
	~PainelDeDebug();

	void inicializar();
	void finalizar();

	void atualizar();
	void desenhar();

	void erro(const string& mensagem, void* ptr = 0);

	void depurar(const string& chave, const string& valor);
	void depurar(const string& chave, const string& valor, const Cor& cor);
	void depurar(const string& chave, int valor);
	void depurar(const string& chave, int valor, const Cor& cor);
	void depurar(const string& chave, unsigned int valor);
	void depurar(const string& chave, unsigned int valor, const Cor& cor);
	void depurar(const string& chave, double valor);
	void depurar(const string& chave, double valor, const Cor& cor);
	void depurar(const string& chave, float valor);
	void depurar(const string& chave, float valor, const Cor& cor);
	void depurar(const string& chave, char valor);
	void depurar(const string& chave, char valor, const Cor& cor);
	void depurar(const string& chave, unsigned char valor);
	void depurar(const string& chave, unsigned char valor, const Cor& cor);
	void depurar(const string& chave, const Vetor2D& valor);
	void depurar(const string& chave, const Vetor2D& valor, const Cor& cor);
	void depurar(const string& chave, const Quad& valor);
	void depurar(const string& chave, const Quad& valor, const Cor& cor);

	void removerErro(int indice);
	void removerDepuracao(int indice);
	void removerDepuracao(const string& chave);

	void limpar();
	void limparErros();
	void limparDepuracoes();

	void ativar();
	void desativar();

	void mostrar();
	void esconder();

	void minimizar();
	void restaurar();

	int getX();
	int getY();
	Cor getCorFundo();
	Cor getCorContorno();
	Cor getCorTitulo();
	Cor getCorErro();
	Cor getCorDepuracao();

	bool estaAtivo();
	bool estaVisivel();
	bool estaMinimizado();

	void setAtivo(bool ativo);
	void setVisivel(bool visivel);
	void setX(int x);
	void setY(int y);
	void setPos(int x, int y);
	void setCorFundo(Cor cor);
	void setCorContorno(Cor cor);
	void setCorTitulo(Cor cor);
	void setCorErro(Cor cor, bool mudarTodos = true);
	void setCorDepuracao(Cor cor, bool mudarTodos = true);

private:
	void atualizarTamanhoTitulo();
	void atualizarTamanhoBotaoFechar();
	void atualizarCliqueBotaoFechar();
	void atualizarTamanhoBotaoMinimizar();
	void atualizarCliqueBotaoMinimizar();
	void atualizarMoverPainel();

	void desenharTitulo(int &proxY);
	void desenharBotaoFechar();
	void desenharBotaoMinimizar();
	void desenharItem(ItemDebug item, int x, int y, int larg, int &proxY);

	vector<ItemDebug> itensErro;
	vector<ItemDebug> itensDepurar;

	bool ativo;
	bool visivel;
	bool minimizado;
	bool movendo;

	int x;
	int y;
	int maiorLargura;
	int meio;
	Vetor2D escalaGlobal;
	Quad retanTitulo;
	Quad retanFechar;
	Quad retanMinimizar;
	
	Cor corFundo;
	Cor corContorno;
	Cor corTitulo;
	Cor corErro;
	Cor corDepuracao;
};

#endif