#ifndef UNI_JANELA_H
#define UNI_JANELA_H

#include "uniAPI.h"
#include "uniPlataformas.h"
#include "Quad.h"
#include "Fading.h"
#include "SDL.h"
#include <string>

using namespace std;

class UNI_API Janela
{
public:
	Janela();
	~Janela();

	bool criar(int largura, int altura, bool tela_cheia, string titulo_janela, int sdl_window_flags = 0);
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
	int getLarguraReal();
	int getAlturaReal();
	int getLarguraTotal();
	int getAlturaTotal();

	void obterPos(int &x, int &y);
	void obterTamanho(int &larg, int &alt);
	void obterTamanhoReal(int &larg, int &alt);
	void obterTamanhoTotal(int &larg, int &alt);
	void obterCorDeFundo(int &vermelho, int &verde, int &azul);

	bool estaEmModoPaisagem();
	bool estaEmModoRetrato();
	bool estaEmTelaCheia();

	bool setIcone(string caminho_arquivo);

	void setTitulo(string titulo);
	void setPos(int x, int y);
	void setTamanho(int larg, int alt);
	void setTamanhoReal(int larg, int alt);
	void setCorDeFundo(const Cor& cor);
	void setCorDeFundo(int vermelhor, int verde, int azul);
	void setTelaCheia(bool tela_cheia);

	void ajustar();
	void limpar();
	void desenhar();
	void removerRetanguloDeCorte();
	void removerLetterBoxing();

	SDL_Renderer* getSDL_Renderer();
	SDL_Window* getSDL_Window();

	Fading fading;

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
	int largura_real;
	int altura_real;
	int id;

	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;

	SDL_Color cor;
	static bool criada;
};

#endif
