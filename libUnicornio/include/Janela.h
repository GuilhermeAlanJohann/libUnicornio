#ifndef UNI_JANELA_H
#define UNI_JANELA_H

#include "uniPlataformas.h"
#include "SDL.h"
#include <string>

using namespace std;

class Janela
{
public:
	Janela();
	~Janela();

	bool criar(int largura, int altura, bool tela_cheia, string titulo_janela);
	bool destruir();

	void limparEventos();
	void processarEvento(const SDL_Event& evento);

	bool moveu();
	bool mudouTamanho();
	bool minimizou();
	bool maximizou();
	bool restaurou();
	bool mouseEntrou();
	bool mouseEstaDentro();
	bool mouseSaiu();
	bool ganhouFoco();
	bool estaEmFoco();
	bool perdeuFoco();
	bool clicouFechar();

	int getID();
	
	string getTitulo();
	int getX();
	int getY();
	int getLargura();
	int getAltura();
	int getLarguraTela();
	int getAlturaTela();

	void obterPos(int &x, int &y);
	void obterTamanho(int &larg, int &alt);
	void obterTamanhoTela(int &larg, int &alt);
	void obterCorDeFundo(int &vermelho, int &verde, int &azul);

	bool estaEmModoPaisagem();
	bool estaEmModoRetrato();
	bool telaEstaEmModoPaisagem();
	bool telaEstaEmModoRetrato();
	bool estaEmTelaCheia();

	bool setIcone(string caminho_arquivo);

	void setTitulo(string titulo);
	void setPos(int x, int y);
	void setTamanho(int larg, int alt);
	void setTamanhoTela(int larg, int alt);
	void setCorDeFundo(int vermelhor, int verde, int azul);
	void setTelaCheia(bool tela_cheia);

	void ajustarTela();
	void limpar();
	void desenhar();

	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;

private:
	bool moveu_;
	bool mudou_tamanho;
	bool minimizou_;
	bool maximizou_;
	bool restaurou_;
	bool mouse_entrou;
	bool mouse_esta_dentro;
	bool mouse_saiu;
	bool ganhou_foco;
	bool esta_em_foco;
	bool perdeu_foco;
	bool clicou_fechar;

	int x;
	int y;
	int largura;
	int altura;
	int largura_tela;
	int altura_tela;
	int id;

	SDL_Color cor;
	static bool criada;
};

#endif
