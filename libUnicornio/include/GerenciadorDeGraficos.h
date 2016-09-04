#ifndef UNI_GERENCIADORDEGRAFICOS_H
#define UNI_GERENCIADORDEGRAFICOS_H

#include "uniAPI.h"
#include "Vetor2D.h"
#include "Fonte.h"
#include "SDL.h"
#include "TexturaBase.h"

class UNI_API GerenciadorDeGraficos
{
public:
	GerenciadorDeGraficos();
	~GerenciadorDeGraficos();

	void inicializar(SDL_Renderer* renderer);
	void finalizar();

	void setLimites(const Quad& limites);
	void unsetLimites();
	Quad getLimites();

	void desenharPixel(int x, int y, int r = 255, int g = 255, int b = 255, int a = 255);
	void desenharLinha(int x1, int y1, int x2, int y2, int r = 255, int g = 255, int b = 255, int a = 255);

	void desenharRetangulo(const Quad& retangulo, int r = 255, int g = 255, int b = 255, int a = 255, bool preencher = false);
	void desenharRetangulo(int x, int y, float rot, int largura, int altura, float ancora_x, float ancora_y, int r = 255, int g = 255, int b = 255, int a = 255, bool preencher = false);
	void desenharRetanguloArredondado(int x, int y, int largura, int altura, float ancora_x, float ancora_y, int raio, int r = 255, int g = 255, int b = 255, int a = 255, bool preencher = false);

	void desenharArco(int x, int y, float raio, float angulo_inicial, float angulo_final, int r = 255, int g = 255, int b = 255, int a = 255);
	void desenharCirculo(int x, int y, float raio, int r = 255, int g = 255, int b = 255, int a = 255, bool preencher = false);
	void desenharSemiCirculo(int x, int y, float raio, float angulo_inicial, float angulo_final, int r = 255, int g = 255, int b = 255, int a = 255, bool preencher = false);
	void desenharElipse(int x, int y, float raio_x, float raio_y, int r = 255, int g = 255, int b = 255, int a = 255, bool preencher = false);

	void desenharPoligono(int x, int y, float rot, Vetor2D* pontos, int num_pontos, int r = 255, int g = 255, int b = 255, int a = 255, bool preencher = false);

	void desenharTexto(const string& str, int x, int y, int r = 255, int g = 255, int b = 255, int a = 255, float ancora_x = 0.5f, float ancora_y = 0.5f);

	bool desenharTextura(TexturaBase* textura, const Quad& retangulo, const Quad& destino, Cor cor = Cor(255, 255, 255, 255));
	bool desenharTextura(TexturaBase* textura, const Quad& retangulo, const Quad& destino, float rot, int centro_x, int centro_y, Cor cor = Cor(255, 255, 255, 255), EnumInverterDesenho inverter = NAO_INVERTER);
	bool desenharTextura(TexturaBase* textura, const Quad& retangulo, int x, int y, float rot = 0.0f, float ancora_x = 0.5f, float ancora_y = 0.5f, float escala_x = 1.0f, float escala_y = 1.0f, Cor cor = Cor(255, 255, 255, 255), EnumInverterDesenho inverter = NAO_INVERTER);

	Fonte* getFontePadrao();
	SDL_Texture* getSDL_TextureBranco();

	//	Membro público (muito usado, então deixei público)
	SDL_Renderer* sdl_renderer;

private:
	void carregarFontePadrao();
	void descarregarFontePadrao();
	void criarSDL_TextureBranco();
	void destruirSDL_TextureBranco();

	SDL_Point* _mallocLinhasPoligono(const Vetor2D* pontos, int num_pontos, int x, int y, float rot);
	int _poligono(SDL_Renderer * renderer, int x, int y, float rot, Vetor2D* pontos, int num_pontos, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	int _poligonoPreenchido(SDL_Renderer * renderer, int x, int y, float rot, Vetor2D* pontos, int num_pontos, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int **polyInts, int *polyAllocated);

	//	Membros
	Fonte* fontePadrao;
	SDL_Texture* sdl_textureBranco;


	//	*****************
	//	**** SDL_GFX ****
	//	*****************

	/* Pixel */
	int pixelRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	int pixelRGBAWeight(SDL_Renderer * renderer, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint32 weight);

	/* Horizontal line */
	int hline(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y);
	int hlineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Vertical line */
	int vlineRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y1, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Rectangle */
	int rectangleRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Rounded-Corner Rectangle */
	int roundedRectangleRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Filled rectangle (Box) */
	int boxRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Rounded-Corner Filled rectangle (Box) */
	int roundedBoxRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Line */
	int lineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* AA Line */
	int _aalineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int draw_endpoint);
	int aalineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Circle */
	int circleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Arc */
	int arcRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* AA Circle */
	int aacircleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Filled Circle */
	int filledCircleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Ellipse */
	int ellipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* AA Ellipse */
	int aaellipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Filled Ellipse */
	int filledEllipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Pie And Filled Pie*/
	int _pieRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 filled);

	/* Trigon */
	int trigonRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* AA-Trigon */
	int aatrigonRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Filled Trigon */
	int filledTrigonRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Polygon */
	int polygon(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n);
	int polygonRGBA(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* AA-Polygon */
	int aapolygonRGBA(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Filled Polygon */
	int filledPolygonRGBA(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	int filledPolygonRGBAMT(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int **polyInts, int *polyAllocated);

	/* Other */
	static int _gfxPrimitivesCompareInt(const void *a, const void *b);
	static int *gfxPrimitivesPolyIntsGlobal;
	static int gfxPrimitivesPolyAllocatedGlobal;
};

#endif