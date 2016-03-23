#ifndef UNI_GERENCIADORDEGRAFICOS_H
#define UNI_GERENCIADORDEGRAFICOS_H

#include "Vetor2D.h"
#include "Fonte.h"
#include "SDL.h"

class GerenciadorDeGraficos
{
public:
	GerenciadorDeGraficos();
	~GerenciadorDeGraficos();

	void inicializar();
	void finalizar();

	void desenharPixel(int x, int y, int vermelho = 255, int verde = 255, int azul = 255, int alpha = 255);
	void desenharLinha(int x1, int y1, int x2, int y2, int vermelho = 255, int verde = 255, int azul = 255, int alpha = 255);
	void desenharCirculo(int x, int y, float raio, int num_segmentos, int vermelho = 255, int verde = 255, int azul = 255);
	void desenharRetangulo(const Retangulo& retangulo, int vermelho = 255, int verde = 255, int azul = 255);
	void desenharRetangulo(int x, int y, float rot, int largura, int altura, float ancora_x, float ancora_y, int vermelho = 255, int verde = 255, int azul = 255);
	void desenharPoligono(int x, int y, float rot, Vetor2D* pontos, int num_pontos, int vermelho = 255, int verde = 255, int azul = 255);
	void desenharTexto(string txt, int x, int y, int vermelho = 255, int verde = 255, int azul = 255, int alpha = 255, float ancora_x = 0.5f, float ancora_y = 0.5f);
	void desenharSDL_Texture(SDL_Texture* texture, const Retangulo& recorte, const Vetor2D& escala, const Vetor2D& ancora, const Vetor2D& pos, float rot = 0.0f, SDL_RendererFlip flip_mode = SDL_FLIP_NONE, const Cor& cor = Cor(255, 255, 255, 255));

	Fonte* getFontePadrao();
	SDL_Texture* getSDL_TextureBranco();

private:
	void carregarFontePadrao();
	void descarregarFontePadrao();
	void criarSDL_TextureBranco();
	void destruirSDL_TextureBranco();

	Fonte* fontePadrao;
	SDL_Texture* sdl_textureBranco;
};

#endif