#include "GerenciadorDeGraficos.h"
#include "uniFuncoesPrincipais.h"
#include "Global.h"
#include "Texto.h"
#include "uniPlataformas.h"

#if UNI_PLATAFORMA_MOVEL || UNI_PLATAFORMA_MAC
#include <float.h>
#endif

GerenciadorDeGraficos::GerenciadorDeGraficos()
{
	fontePadrao = NULL;
	sdl_textureBranco = NULL;
	sdl_renderer = NULL;
}

GerenciadorDeGraficos::~GerenciadorDeGraficos()
{
}

void GerenciadorDeGraficos::inicializar(SDL_Renderer* renderer)
{
	sdl_renderer = renderer;
	carregarFontePadrao();
	criarSDL_TextureBranco();
}

void GerenciadorDeGraficos::finalizar()
{
	destruirSDL_TextureBranco();
	descarregarFontePadrao();
	sdl_renderer = NULL;
}

void GerenciadorDeGraficos::setLimites(const Quad& limites)
{
	if (limites.larg <= 0 && limites.alt <= 0)
	{
		unsetLimites();
	}
	else
	{
		SDL_Rect rect = limites.getSDL_Rect();
		SDL_RenderSetClipRect(sdl_renderer, &rect);
	}
}

void GerenciadorDeGraficos::unsetLimites()
{
	SDL_RenderSetClipRect(sdl_renderer, NULL);
}

Quad GerenciadorDeGraficos::getLimites()
{
	SDL_Rect rect;
	SDL_RenderGetClipRect(sdl_renderer, &rect);
	return Quad(rect.x, rect.y, rect.w, rect.h);
}

void GerenciadorDeGraficos::desenharPixel(int x, int y, int r, int g, int b, int a)
{
	pixelRGBA(sdl_renderer, x, y, r, g, b, a);
}

void GerenciadorDeGraficos::desenharLinha(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
{
	lineRGBA(sdl_renderer, x1, y1, x2, y2, r, g, b, a);
}

void GerenciadorDeGraficos::desenharRetangulo(const Quad& retangulo, int r, int g, int b, int a, bool preencher)
{
	if (retangulo.larg == 0 || retangulo.alt == 0)
		return;
	
	int dx, dy;
	if (retangulo.larg < 0)
		dx = 1;
	else
		dx = -1;

	if (retangulo.alt < 0)
		dy = 1;
	else
		dy = -1;

	if (preencher)
		boxRGBA(sdl_renderer, retangulo.x, retangulo.y, retangulo.x + retangulo.larg + dx, retangulo.y + retangulo.alt + dy, r, g, b, a);
	else
		rectangleRGBA(sdl_renderer, retangulo.x, retangulo.y, retangulo.x + retangulo.larg + dx, retangulo.y + retangulo.alt + dy, r, g, b, a);
}

void GerenciadorDeGraficos::desenharRetangulo(int x, int y, float rot, int largura, int altura, float ancora_x, float ancora_y, int r, int g, int b, int a, bool preencher)
{
	if (rot == 0.0f)
	{
		int x1 = x - largura*ancora_x;
		int y1 = y - altura*ancora_y;
		desenharRetangulo(Quad(x1, y1, largura, altura), r, g, b, a, preencher);
	}
	else
	{
		if (largura == 0 || altura == 0)
			return;

		Vetor2D pontos[4];
		float x1 = -largura*ancora_x;
		float y1 = -altura*ancora_y;
		pontos[0].set(x1, y1);
		pontos[1].set(x1, y1 + altura );
		pontos[2].set(x1 + largura, y1 + altura);
		pontos[3].set(x1 + largura, y1);
		desenharPoligono(x, y, rot, pontos, 4, r, g, b, a, preencher);
	}
}

void GerenciadorDeGraficos::desenharRetanguloArredondado(int x, int y, int largura, int altura, float ancora_x, float ancora_y, int raio, int r, int g, int b, int a, bool preencher)
{
	if (largura == 0 || altura == 0)
		return;

	int dx, dy;
	if (largura < 0)
		dx = 1;
	else
		dx = -1;

	if (altura < 0)
		dy = 1;
	else
		dy = -1;

	int x1 = x - largura*ancora_x;
	int y1 = y - altura*ancora_y;
	if (preencher)
		roundedBoxRGBA(sdl_renderer, x1, y1, x1 + largura + dx, y1 + altura + dy, raio, r, g, b, a);
	else
		roundedRectangleRGBA(sdl_renderer, x1, y1, x1 + largura + dx, y1 + altura + dy, raio, r, g, b, a);
}

void GerenciadorDeGraficos::desenharArco(int x, int y, float raio, float angulo_inicial, float angulo_final, int r, int g, int b, int a)
{
	arcRGBA(sdl_renderer, x, y, raio, angulo_inicial, angulo_final, r, g, b, a);
}

void GerenciadorDeGraficos::desenharCirculo(int x, int y, float raio, int r, int g, int b, int a, bool preencher)
{
	if (preencher)
		filledCircleRGBA(sdl_renderer, x, y, raio, r, g, b, a);
	else
		circleRGBA(sdl_renderer, x, y, raio, r, g, b, a);
}

void GerenciadorDeGraficos::desenharSemiCirculo(int x, int y, float raio, float angulo_inicial, float angulo_final, int r, int g, int b, int a, bool preencher)
{
	_pieRGBA(sdl_renderer, x, y, raio, angulo_inicial, angulo_final, r, g, b, a, (Uint8)preencher);
}

void GerenciadorDeGraficos::desenharElipse(int x, int y, float raio_x, float raio_y, int r, int g, int b, int a, bool preencher)
{
	if (preencher)
		filledEllipseRGBA(sdl_renderer, x, y, raio_x, raio_y, r, g, b, a);
	else
		ellipseRGBA(sdl_renderer, x, y, raio_x, raio_y, r, g, b, a);
}

void GerenciadorDeGraficos::desenharPoligono(int x, int y, float rot, Vetor2D* pontos, int num_pontos, int r, int g, int b, int a, bool preencher)
{
	if (!pontos)
		return;

	if (preencher)
		_poligonoPreenchido(sdl_renderer, x, y, rot, pontos, num_pontos, r, g, b, a, NULL, NULL);
	else
		_poligono(sdl_renderer, x, y, rot, pontos, num_pontos, r, g, b, a);

}

void GerenciadorDeGraficos::desenharTexto(const string& str, int x, int y, int r, int g, int b, int a, float ancora_x, float ancora_y)
{
	if (!fontePadrao)
		return;

	Texto t;
	t.setFonte(fontePadrao);
	t.setString(str);
	t.setCor(r, g, b, a);

	t.setAncora(ancora_x, ancora_y);

	t.desenhar(x, y);
}

bool GerenciadorDeGraficos::desenharTextura(TexturaBase* textura, const Quad& retangulo, const Quad& destino, Cor cor)
{
	SDL_Rect src = retangulo.getSDL_Rect();
	SDL_Rect dest = destino.getSDL_Rect();

	SDL_Texture* sdl_texture = textura->getSDL_Texture();
	SDL_SetTextureColorMod(sdl_texture, cor.r, cor.g, cor.b);
	SDL_SetTextureAlphaMod(sdl_texture, cor.a);
	return (SDL_RenderCopy(gGraficos.sdl_renderer, sdl_texture, &src, &dest) == 0);
}

bool GerenciadorDeGraficos::desenharTextura(TexturaBase* textura, const Quad& retangulo, const Quad& destino, float rot, int centro_x, int centro_y, Cor cor, EnumInverterDesenho inverter)
{
	SDL_Rect src = retangulo.getSDL_Rect();
	SDL_Rect dest = destino.getSDL_Rect();
	SDL_Point center = { centro_y, centro_y };

	SDL_Texture* sdl_texture = textura->getSDL_Texture();
	SDL_SetTextureColorMod(sdl_texture, cor.r, cor.g, cor.b);
	SDL_SetTextureAlphaMod(sdl_texture, cor.a);
	return (SDL_RenderCopyEx(gGraficos.sdl_renderer, sdl_texture, &src, &dest, rot, &center, (SDL_RendererFlip)inverter) == 0);
}

bool GerenciadorDeGraficos::desenharTextura(TexturaBase* textura, const Quad& retangulo, int x, int y, float rot, float ancora_x, float ancora_y, float escala_x, float escala_y, Cor cor, EnumInverterDesenho inverter)
{
	SDL_Rect src = retangulo.getSDL_Rect();
	SDL_Rect dest = { x, y, (int)(src.w*escala_x), (int)(src.h*escala_y) };
	dest.x -= dest.w*ancora_x;
	dest.y -= dest.h*ancora_y;

	SDL_Point center = { (int)(dest.w * ancora_x), (int)(dest.h * ancora_y) };

	SDL_Texture* sdl_texture = textura->getSDL_Texture();
	SDL_SetTextureColorMod(sdl_texture, cor.r, cor.g, cor.b);
	SDL_SetTextureAlphaMod(sdl_texture, cor.a);
	return (SDL_RenderCopyEx(gGraficos.sdl_renderer, sdl_texture, &src, &dest, rot, &center, (SDL_RendererFlip)inverter) == 0);
}


Fonte* GerenciadorDeGraficos::getFontePadrao()
{
	return fontePadrao;
}

SDL_Texture* GerenciadorDeGraficos::getSDL_TextureBranco()
{
	return sdl_textureBranco;
}

void GerenciadorDeGraficos::carregarFontePadrao()
{
	fontePadrao = new Fonte;
	if (fontePadrao->carregar("fonte_padrao.ttf", 10) == false)
	{
		delete fontePadrao;
		fontePadrao = NULL;
		//  limpa o painel de debug e desativa, para nao tentar desenhar sem ter uma fonte.
		gDebug.limpar();
		gDebug.desativar();
	}
}

void GerenciadorDeGraficos::descarregarFontePadrao()
{
	if (fontePadrao)
	{
		fontePadrao->descarregar();
		delete fontePadrao;
		fontePadrao = NULL;
	}
}

void GerenciadorDeGraficos::criarSDL_TextureBranco()
{
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	SDL_Surface* surface = SDL_CreateRGBSurface(0, 8, 8, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 255, 255, 255));

	sdl_textureBranco = SDL_CreateTextureFromSurface(sdl_renderer, surface);
	SDL_SetTextureBlendMode(sdl_textureBranco, SDL_BLENDMODE_BLEND);

	SDL_FreeSurface(surface);
}

void GerenciadorDeGraficos::destruirSDL_TextureBranco()
{
	SDL_DestroyTexture(sdl_textureBranco);
	sdl_textureBranco = NULL;
}


SDL_Point* GerenciadorDeGraficos::_mallocLinhasPoligono(const Vetor2D* pontos, int num_pontos, int x, int y, float rot)
{
	/*
	* Create array of points
	*/
	int n = num_pontos + 1;
	SDL_Point* points = (SDL_Point*)malloc(sizeof(SDL_Point) * n);

	if (!points)
		return NULL;
	
	float cs = SDL_cosf(rot*(float)(M_PI / 180.0));
	float sn = SDL_sinf(rot*(float)(M_PI / 180.0));

	if (fabsf(cs) < FLT_EPSILON)
		cs = 0.0f;
	if (fabsf(sn) < FLT_EPSILON)
		sn = 0.0f;

	for (int i = 0; i < num_pontos; i++)
	{
		//	rotaciona os pontos (em relação a origem)
		float xx = pontos[i].x * cs - pontos[i].y * sn;
		float yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos para posição
		points[i].x = (int)xx + x;
		points[i].y = (int)yy + y;
	}
	points[num_pontos] = points[0];
	return points;
}

int GerenciadorDeGraficos::_poligono(SDL_Renderer * renderer, int x, int y, float rot, Vetor2D* pontos, int num_pontos, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Sanity check number of edges
	*/
	if (num_pontos < 3)
		return -1;

	//	Alloc
	SDL_Point* points = _mallocLinhasPoligono(pontos, num_pontos, x, y, rot);

	/*
	* Vertex array NULL check
	*/
	if (points == NULL)
		return -1;

	/*
	* Draw
	*/
	int result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderDrawLines(renderer, points, num_pontos + 1);

	//	Free
	free(points);

	//	Return
	return (result);
}

int GerenciadorDeGraficos::_poligonoPreenchido(SDL_Renderer * renderer, int _x, int _y, float rot, Vetor2D* pontos, int num_pontos, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int **polyInts, int *polyAllocated)
{
	int result;
	int i;
	int y, xa, xb;
	int miny, maxy;
	int x1, y1;
	int x2, y2;
	int ind1, ind2;
	int ints;
	int *gfxPrimitivesPolyInts = NULL;
	int *gfxPrimitivesPolyIntsNew = NULL;
	int gfxPrimitivesPolyAllocated = 0;

	/*
	* Sanity check number of edges
	*/
	if (num_pontos < 3)
		return -1;

	//	Alloc
	SDL_Point* points = _mallocLinhasPoligono(pontos, num_pontos, _x, _y, rot);
	int n = num_pontos + 1;

	/*
	* Vertex array NULL check
	*/
	if (points == NULL)
		return -1;

	/*
	* Map polygon cache
	*/
	if ((polyInts == NULL) || (polyAllocated == NULL)) {
		/* Use global cache */
		gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsGlobal;
		gfxPrimitivesPolyAllocated = gfxPrimitivesPolyAllocatedGlobal;
	}
	else {
		/* Use local cache */
		gfxPrimitivesPolyInts = *polyInts;
		gfxPrimitivesPolyAllocated = *polyAllocated;
	}

	/*
	* Allocate temp array, only grow array
	*/
	if (!gfxPrimitivesPolyAllocated) {
		gfxPrimitivesPolyInts = (int *)malloc(sizeof(int) * n);
		gfxPrimitivesPolyAllocated = n;
	}
	else {
		if (gfxPrimitivesPolyAllocated < n) {
			gfxPrimitivesPolyIntsNew = (int *)realloc(gfxPrimitivesPolyInts, sizeof(int) * n);
			if (!gfxPrimitivesPolyIntsNew) {
				if (!gfxPrimitivesPolyInts) {
					free(gfxPrimitivesPolyInts);
					gfxPrimitivesPolyInts = NULL;
				}
				gfxPrimitivesPolyAllocated = 0;
			}
			else {
				gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsNew;
				gfxPrimitivesPolyAllocated = n;
			}
		}
	}

	/*
	* Check temp array
	*/
	if (gfxPrimitivesPolyInts == NULL) {
		gfxPrimitivesPolyAllocated = 0;
	}

	/*
	* Update cache variables
	*/
	if ((polyInts == NULL) || (polyAllocated == NULL)) {
		gfxPrimitivesPolyIntsGlobal = gfxPrimitivesPolyInts;
		gfxPrimitivesPolyAllocatedGlobal = gfxPrimitivesPolyAllocated;
	}
	else {
		*polyInts = gfxPrimitivesPolyInts;
		*polyAllocated = gfxPrimitivesPolyAllocated;
	}

	/*
	* Check temp array again
	*/
	if (gfxPrimitivesPolyInts == NULL) {
		return(-1);
	}

	/*
	* Determine Y maxima
	*/
	miny = points[0].y;
	maxy = points[0].y;
	for (i = 1; (i < n); i++) {
		if (points[i].y < miny) {
			miny = points[i].y;
		}
		else if (points[i].y > maxy) {
			maxy = points[i].y;
		}
	}

	/*
	* Draw, scanning y
	*/
	result = 0;
	for (y = miny; (y <= maxy); y++) {
		ints = 0;
		for (i = 0; (i < n); i++) {
			if (!i) {
				ind1 = n - 1;
				ind2 = 0;
			}
			else {
				ind1 = i - 1;
				ind2 = i;
			}
			y1 = points[ind1].y;
			y2 = points[ind2].y;
			if (y1 < y2) {
				x1 = points[ind1].x;
				x2 = points[ind2].x;
			}
			else if (y1 > y2) {
				y2 = points[ind1].y;
				y1 = points[ind2].y;
				x2 = points[ind1].x;
				x1 = points[ind2].x;
			}
			else {
				continue;
			}
			if (((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2))) {
				gfxPrimitivesPolyInts[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
			}
		}

		qsort(gfxPrimitivesPolyInts, ints, sizeof(int), _gfxPrimitivesCompareInt);

		/*
		* Set color
		*/
		result = 0;
		result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
		result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

		for (i = 0; (i < ints); i += 2) {
			xa = gfxPrimitivesPolyInts[i] + 1;
			xa = (xa >> 16) + ((xa & 32768) >> 15);
			xb = gfxPrimitivesPolyInts[i + 1] - 1;
			xb = (xb >> 16) + ((xb & 32768) >> 15);
			result |= hline(renderer, xa, xb, y);
		}
	}

	//	Free
	free(points);

	return (result);
}





//	****************************
//	********* SDL_GFX **********
//	****************************

/*!
\brief Draw pixel with blending enabled if a<255.

\param renderer The renderer to draw on.
\param x X (horizontal) coordinate of the pixel.
\param y Y (vertical) coordinate of the pixel.
\param r The red color value of the pixel to draw.
\param g The green color value of the pixel to draw.
\param b The blue color value of the pixel to draw.
\param a The alpha value of the pixel to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::pixelRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderDrawPoint(renderer, x, y);
	return result;
}

/*!
\brief Draw pixel with blending enabled and using alpha weight on color.

\param renderer The renderer to draw on.
\param x The horizontal coordinate of the pixel.
\param y The vertical position of the pixel.
\param r The red color value of the pixel to draw.
\param g The green color value of the pixel to draw.
\param b The blue color value of the pixel to draw.
\param a The alpha value of the pixel to draw.
\param weight The weight multiplied into the alpha value of the pixel.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::pixelRGBAWeight(SDL_Renderer * renderer, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint32 weight)
{
	/*
	* Modify Alpha by weight
	*/
	Uint32 ax = a;
	ax = ((ax * weight) >> 8);
	if (ax > 255) {
		a = 255;
	}
	else {
		a = (Uint8)(ax & 0x000000ff);
	}

	return pixelRGBA(renderer, x, y, r, g, b, a);
}

/* ---- Hline */

/*!
\brief Draw horizontal line in currently set color

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. left) of the line.
\param x2 X coordinate of the second point (i.e. right) of the line.
\param y Y coordinate of the points of the line.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::hline(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y)
{
	return SDL_RenderDrawLine(renderer, x1, y, x2, y);;
}

/*!
\brief Draw horizontal line with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. left) of the line.
\param x2 X coordinate of the second point (i.e. right) of the line.
\param y Y coordinate of the points of the line.
\param r The red value of the line to draw.
\param g The green value of the line to draw.
\param b The blue value of the line to draw.
\param a The alpha value of the line to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::hlineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderDrawLine(renderer, x1, y, x2, y);
	return result;
}

/* ---- Vline */

/*!
\brief Draw vertical line with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the points of the line.
\param y1 Y coordinate of the first point (i.e. top) of the line.
\param y2 Y coordinate of the second point (i.e. bottom) of the line.
\param r The red value of the line to draw.
\param g The green value of the line to draw.
\param b The blue value of the line to draw.
\param a The alpha value of the line to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::vlineRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y1, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderDrawLine(renderer, x, y1, x, y2);
	return result;
}

/* ---- Rectangle */

/*!
\brief Draw rectangle with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the rectangle.
\param y1 Y coordinate of the first point (i.e. top right) of the rectangle.
\param x2 X coordinate of the second point (i.e. bottom left) of the rectangle.
\param y2 Y coordinate of the second point (i.e. bottom left) of the rectangle.
\param r The red value of the rectangle to draw.
\param g The green value of the rectangle to draw.
\param b The blue value of the rectangle to draw.
\param a The alpha value of the rectangle to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::rectangleRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	Sint16 tmp;
	SDL_Rect rect;

	/*
	* Test for special cases of straight lines or single point
	*/
	if (x1 == x2) {
		if (y1 == y2) {
			return (pixelRGBA(renderer, x1, y1, r, g, b, a));
		}
		else {
			return (vlineRGBA(renderer, x1, y1, y2, r, g, b, a));
		}
	}
	else {
		if (y1 == y2) {
			return (hlineRGBA(renderer, x1, x2, y1, r, g, b, a));
		}
	}

	/*
	* Swap x1, x2 if required
	*/
	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}

	/*
	* Swap y1, y2 if required
	*/
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	/*
	* Create destination rect
	*/
	rect.x = x1;
	rect.y = y1;
	rect.w = x2 - x1 + 1;
	rect.h = y2 - y1 + 1;

	/*
	* Draw
	*/
	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderDrawRect(renderer, &rect);
	return result;
}

/* ---- Rounded Rectangle */

/*!
\brief Draw rounded-corner rectangle with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the rectangle.
\param y1 Y coordinate of the first point (i.e. top right) of the rectangle.
\param x2 X coordinate of the second point (i.e. bottom left) of the rectangle.
\param y2 Y coordinate of the second point (i.e. bottom left) of the rectangle.
\param rad The radius of the corner arc.
\param r The red value of the rectangle to draw.
\param g The green value of the rectangle to draw.
\param b The blue value of the rectangle to draw.
\param a The alpha value of the rectangle to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::roundedRectangleRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result = 0;
	Sint16 tmp;
	Sint16 w, h;
	Sint16 xx1, xx2;
	Sint16 yy1, yy2;

	/*
	* Check renderer
	*/
	if (renderer == NULL)
	{
		return -1;
	}

	/*
	* Check radius vor valid range
	*/
	if (rad < 0) {
		return -1;
	}

	/*
	* Special case - no rounding
	*/
	if (rad <= 1) {
		return rectangleRGBA(renderer, x1, y1, x2, y2, r, g, b, a);
	}

	/*
	* Test for special cases of straight lines or single point
	*/
	if (x1 == x2) {
		if (y1 == y2) {
			return (pixelRGBA(renderer, x1, y1, r, g, b, a));
		}
		else {
			return (vlineRGBA(renderer, x1, y1, y2, r, g, b, a));
		}
	}
	else {
		if (y1 == y2) {
			return (hlineRGBA(renderer, x1, x2, y1, r, g, b, a));
		}
	}

	/*
	* Swap x1, x2 if required
	*/
	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}

	/*
	* Swap y1, y2 if required
	*/
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	/*
	* Calculate width&height
	*/
	w = x2 - x1 + 1;
	h = y2 - y1 + 1;

	/*
	* Maybe adjust radius
	*/
	if ((rad * 2) > w)
	{
		rad = w / 2;
	}
	if ((rad * 2) > h)
	{
		rad = h / 2;
	}

	/*
	* Draw corners
	*/
	xx1 = x1 + rad;
	xx2 = x2 - rad;
	yy1 = y1 + rad;
	yy2 = y2 - rad;
	result |= arcRGBA(renderer, xx1, yy1, rad, 180, 270, r, g, b, a);
	result |= arcRGBA(renderer, xx2, yy1, rad, 270, 360, r, g, b, a);
	result |= arcRGBA(renderer, xx1, yy2, rad, 90, 180, r, g, b, a);
	result |= arcRGBA(renderer, xx2, yy2, rad, 0, 90, r, g, b, a);

	/*
	* Draw lines
	*/
	if (xx1 <= xx2) {
		result |= hlineRGBA(renderer, xx1, xx2, y1, r, g, b, a);
		result |= hlineRGBA(renderer, xx1, xx2, y2, r, g, b, a);
	}
	if (yy1 <= yy2) {
		result |= vlineRGBA(renderer, x1, yy1, yy2, r, g, b, a);
		result |= vlineRGBA(renderer, x2, yy1, yy2, r, g, b, a);
	}

	return result;
}

/* ---- Rounded Box */

/*!
\brief Draw rounded-corner box (filled rectangle) with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the box.
\param y1 Y coordinate of the first point (i.e. top right) of the box.
\param x2 X coordinate of the second point (i.e. bottom left) of the box.
\param y2 Y coordinate of the second point (i.e. bottom left) of the box.
\param rad The radius of the corner arcs of the box.
\param r The red value of the box to draw.
\param g The green value of the box to draw.
\param b The blue value of the box to draw.
\param a The alpha value of the box to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::roundedBoxRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
	Sint16 y2, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	Sint16 w, h, r2, tmp;
	Sint16 cx = 0;
	Sint16 cy = rad;
	Sint16 ocx = (Sint16)0xffff;
	Sint16 ocy = (Sint16)0xffff;
	Sint16 df = 1 - rad;
	Sint16 d_e = 3;
	Sint16 d_se = -2 * rad + 5;
	Sint16 xpcx, xmcx, xpcy, xmcy;
	Sint16 ypcy, ymcy, ypcx, ymcx;
	Sint16 x, y, dx, dy;

	/*
	* Check destination renderer
	*/
	if (renderer == NULL)
	{
		return -1;
	}

	/*
	* Check radius vor valid range
	*/
	if (rad < 0) {
		return -1;
	}

	/*
	* Special case - no rounding
	*/
	if (rad <= 1) {
		return rectangleRGBA(renderer, x1, y1, x2, y2, r, g, b, a);
	}

	/*
	* Test for special cases of straight lines or single point
	*/
	if (x1 == x2) {
		if (y1 == y2) {
			return (pixelRGBA(renderer, x1, y1, r, g, b, a));
		}
		else {
			return (vlineRGBA(renderer, x1, y1, y2, r, g, b, a));
		}
	}
	else {
		if (y1 == y2) {
			return (hlineRGBA(renderer, x1, x2, y1, r, g, b, a));
		}
	}

	/*
	* Swap x1, x2 if required
	*/
	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}

	/*
	* Swap y1, y2 if required
	*/
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	/*
	* Calculate width&height
	*/
	w = x2 - x1 + 1;
	h = y2 - y1 + 1;

	/*
	* Maybe adjust radius
	*/
	r2 = rad + rad;
	if (r2 > w)
	{
		rad = w / 2;
		r2 = rad + rad;
	}
	if (r2 > h)
	{
		rad = h / 2;
	}

	/* Setup filled circle drawing for corners */
	x = x1 + rad;
	y = y1 + rad;
	dx = x2 - x1 - rad - rad;
	dy = y2 - y1 - rad - rad;

	/*
	* Set color
	*/
	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

	/*
	* Draw corners
	*/
	do {
		xpcx = x + cx;
		xmcx = x - cx;
		xpcy = x + cy;
		xmcy = x - cy;
		if (ocy != cy) {
			if (cy > 0) {
				ypcy = y + cy;
				ymcy = y - cy;
				result |= hline(renderer, xmcx, xpcx + dx, ypcy + dy);
				result |= hline(renderer, xmcx, xpcx + dx, ymcy);
			}
			else {
				result |= hline(renderer, xmcx, xpcx + dx, y);
			}
			ocy = cy;
		}
		if (ocx != cx) {
			if (cx != cy) {
				if (cx > 0) {
					ypcx = y + cx;
					ymcx = y - cx;
					result |= hline(renderer, xmcy, xpcy + dx, ymcx);
					result |= hline(renderer, xmcy, xpcy + dx, ypcx + dy);
				}
				else {
					result |= hline(renderer, xmcy, xpcy + dx, y);
				}
			}
			ocx = cx;
		}

		/*
		* Update
		*/
		if (df < 0) {
			df += d_e;
			d_e += 2;
			d_se += 2;
		}
		else {
			df += d_se;
			d_e += 2;
			d_se += 4;
			cy--;
		}
		cx++;
	} while (cx <= cy);

	/* Inside */
	if (dx > 0 && dy > 0) {
		result |= boxRGBA(renderer, x1, y1 + rad + 1, x2, y2 - rad, r, g, b, a);
	}

	return (result);
}

/* ---- Box */

/*!
\brief Draw box (filled rectangle) with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the box.
\param y1 Y coordinate of the first point (i.e. top right) of the box.
\param x2 X coordinate of the second point (i.e. bottom left) of the box.
\param y2 Y coordinate of the second point (i.e. bottom left) of the box.
\param r The red value of the box to draw.
\param g The green value of the box to draw.
\param b The blue value of the box to draw.
\param a The alpha value of the box to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::boxRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	Sint16 tmp;
	SDL_Rect rect;

	/*
	* Test for special cases of straight lines or single point
	*/
	if (x1 == x2) {
		if (y1 == y2) {
			return (pixelRGBA(renderer, x1, y1, r, g, b, a));
		}
		else {
			return (vlineRGBA(renderer, x1, y1, y2, r, g, b, a));
		}
	}
	else {
		if (y1 == y2) {
			return (hlineRGBA(renderer, x1, x2, y1, r, g, b, a));
		}
	}

	/*
	* Swap x1, x2 if required
	*/
	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}

	/*
	* Swap y1, y2 if required
	*/
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	/*
	* Create destination rect
	*/
	rect.x = x1;
	rect.y = y1;
	rect.w = x2 - x1 + 1;
	rect.h = y2 - y1 + 1;

	/*
	* Draw
	*/
	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderFillRect(renderer, &rect);
	return result;
}

/*!
\brief Draw line with alpha blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the line.
\param y1 Y coordinate of the first point of the line.
\param x2 X coordinate of the second point of the line.
\param y2 Y coordinate of the second point of the line.
\param r The red value of the line to draw.
\param g The green value of the line to draw.
\param b The blue value of the line to draw.
\param a The alpha value of the line to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::lineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw
	*/
	int result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	return result;
}

/* ---- AA Line */

#define AAlevels 256
#define AAbits 8

/*!
\brief Internal function to draw anti-aliased line with alpha blending and endpoint control.

This implementation of the Wu antialiasing code is based on Mike Abrash's
DDJ article which was reprinted as Chapter 42 of his Graphics Programming
Black Book, but has been optimized to work with SDL and utilizes 32-bit
fixed-point arithmetic by A. Schiffler. The endpoint control allows the
supression to draw the last pixel useful for rendering continous aa-lines
with alpha<255.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the aa-line.
\param y1 Y coordinate of the first point of the aa-line.
\param x2 X coordinate of the second point of the aa-line.
\param y2 Y coordinate of the second point of the aa-line.
\param r The red value of the aa-line to draw.
\param g The green value of the aa-line to draw.
\param b The blue value of the aa-line to draw.
\param a The alpha value of the aa-line to draw.
\param draw_endpoint Flag indicating if the endpoint should be drawn; draw if non-zero.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::_aalineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int draw_endpoint)
{
	Sint32 xx0, yy0, xx1, yy1;
	int result;
	Uint32 intshift, erracc, erradj;
	Uint32 erracctmp, wgt, wgtcompmask;
	int dx, dy, tmp, xdir, y0p1, x0pxdir;

	/*
	* Keep on working with 32bit numbers
	*/
	xx0 = x1;
	yy0 = y1;
	xx1 = x2;
	yy1 = y2;

	/*
	* Reorder points to make dy positive
	*/
	if (yy0 > yy1) {
		tmp = yy0;
		yy0 = yy1;
		yy1 = tmp;
		tmp = xx0;
		xx0 = xx1;
		xx1 = tmp;
	}

	/*
	* Calculate distance
	*/
	dx = xx1 - xx0;
	dy = yy1 - yy0;

	/*
	* Adjust for negative dx and set xdir
	*/
	if (dx >= 0) {
		xdir = 1;
	}
	else {
		xdir = -1;
		dx = (-dx);
	}

	/*
	* Check for special cases
	*/
	if (dx == 0) {
		/*
		* Vertical line
		*/
		if (draw_endpoint)
		{
			return (vlineRGBA(renderer, x1, y1, y2, r, g, b, a));
		}
		else {
			if (dy > 0) {
				return (vlineRGBA(renderer, x1, yy0, yy0 + dy, r, g, b, a));
			}
			else {
				return (pixelRGBA(renderer, x1, y1, r, g, b, a));
			}
		}
	}
	else if (dy == 0) {
		/*
		* Horizontal line
		*/
		if (draw_endpoint)
		{
			return (hlineRGBA(renderer, x1, x2, y1, r, g, b, a));
		}
		else {
			if (dx > 0) {
				return (hlineRGBA(renderer, xx0, xx0 + dx, y1, r, g, b, a));
			}
			else {
				return (pixelRGBA(renderer, x1, y1, r, g, b, a));
			}
		}
	}
	else if ((dx == dy) && (draw_endpoint)) {
		/*
		* Diagonal line (with endpoint)
		*/
		return (lineRGBA(renderer, x1, y1, x2, y2, r, g, b, a));
	}


	/*
	* Line is not horizontal, vertical or diagonal (with endpoint)
	*/
	result = 0;

	/*
	* Zero accumulator
	*/
	erracc = 0;

	/*
	* # of bits by which to shift erracc to get intensity level
	*/
	intshift = 32 - AAbits;

	/*
	* Mask used to flip all bits in an intensity weighting
	*/
	wgtcompmask = AAlevels - 1;

	/*
	* Draw the initial pixel in the foreground color
	*/
	result |= pixelRGBA(renderer, x1, y1, r, g, b, a);

	/*
	* x-major or y-major?
	*/
	if (dy > dx) {

		/*
		* y-major.  Calculate 16-bit fixed point fractional part of a pixel that
		* X advances every time Y advances 1 pixel, truncating the result so that
		* we won't overrun the endpoint along the X axis
		*/
		/*
		* Not-so-portable version: erradj = ((Uint64)dx << 32) / (Uint64)dy;
		*/
		erradj = ((dx << 16) / dy) << 16;

		/*
		* draw all pixels other than the first and last
		*/
		x0pxdir = xx0 + xdir;
		while (--dy) {
			erracctmp = erracc;
			erracc += erradj;
			if (erracc <= erracctmp) {
				/*
				* rollover in error accumulator, x coord advances
				*/
				xx0 = x0pxdir;
				x0pxdir += xdir;
			}
			yy0++;		/* y-major so always advance Y */

						/*
						* the AAbits most significant bits of erracc give us the intensity
						* weighting for this pixel, and the complement of the weighting for
						* the paired pixel.
						*/
			wgt = (erracc >> intshift) & 255;
			result |= pixelRGBAWeight(renderer, xx0, yy0, r, g, b, a, 255 - wgt);
			result |= pixelRGBAWeight(renderer, x0pxdir, yy0, r, g, b, a, wgt);
		}

	}
	else {

		/*
		* x-major line.  Calculate 16-bit fixed-point fractional part of a pixel
		* that Y advances each time X advances 1 pixel, truncating the result so
		* that we won't overrun the endpoint along the X axis.
		*/
		/*
		* Not-so-portable version: erradj = ((Uint64)dy << 32) / (Uint64)dx;
		*/
		erradj = ((dy << 16) / dx) << 16;

		/*
		* draw all pixels other than the first and last
		*/
		y0p1 = yy0 + 1;
		while (--dx) {

			erracctmp = erracc;
			erracc += erradj;
			if (erracc <= erracctmp) {
				/*
				* Accumulator turned over, advance y
				*/
				yy0 = y0p1;
				y0p1++;
			}
			xx0 += xdir;	/* x-major so always advance X */
							/*
							* the AAbits most significant bits of erracc give us the intensity
							* weighting for this pixel, and the complement of the weighting for
							* the paired pixel.
							*/
			wgt = (erracc >> intshift) & 255;
			result |= pixelRGBAWeight(renderer, xx0, yy0, r, g, b, a, 255 - wgt);
			result |= pixelRGBAWeight(renderer, xx0, y0p1, r, g, b, a, wgt);
		}
	}

	/*
	* Do we have to draw the endpoint
	*/
	if (draw_endpoint) {
		/*
		* Draw final pixel, always exactly intersected by the line and doesn't
		* need to be weighted.
		*/
		result |= pixelRGBA(renderer, x2, y2, r, g, b, a);
	}

	return (result);
}

/*!
\brief Draw anti-aliased line with alpha blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the aa-line.
\param y1 Y coordinate of the first point of the aa-line.
\param x2 X coordinate of the second point of the aa-line.
\param y2 Y coordinate of the second point of the aa-line.
\param r The red value of the aa-line to draw.
\param g The green value of the aa-line to draw.
\param b The blue value of the aa-line to draw.
\param a The alpha value of the aa-line to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::aalineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return _aalineRGBA(renderer, x1, y1, x2, y2, r, g, b, a, 1);
}

/* ----- Circle */

/*!
\brief Draw circle with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the circle.
\param y Y coordinate of the center of the circle.
\param rad Radius in pixels of the circle.
\param r The red value of the circle to draw.
\param g The green value of the circle to draw.
\param b The blue value of the circle to draw.
\param a The alpha value of the circle to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::circleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return ellipseRGBA(renderer, x, y, rad, rad, r, g, b, a);
}

/* ----- Arc */

/*!
\brief Arc with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the arc.
\param y Y coordinate of the center of the arc.
\param rad Radius in pixels of the arc.
\param start Starting radius in degrees of the arc. 0 degrees is down, increasing counterclockwise.
\param end Ending radius in degrees of the arc. 0 degrees is down, increasing counterclockwise.
\param r The red value of the arc to draw.
\param g The green value of the arc to draw.
\param b The blue value of the arc to draw.
\param a The alpha value of the arc to draw.

\returns Returns 0 on success, -1 on failure.
*/
/* TODO: rewrite algorithm; arc endpoints are not always drawn */
int GerenciadorDeGraficos::arcRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	Sint16 cx = 0;
	Sint16 cy = rad;
	Sint16 df = 1 - rad;
	Sint16 d_e = 3;
	Sint16 d_se = -2 * rad + 5;
	Sint16 xpcx, xmcx, xpcy, xmcy;
	Sint16 ypcy, ymcy, ypcx, ymcx;
	Uint8 drawoct;
	int startoct, endoct, oct, stopval_start = 0, stopval_end = 0;
	double dstart, dend, temp = 0.;

	/*
	* Sanity check radius
	*/
	if (rad < 0) {
		return (-1);
	}

	/*
	* Special case for rad=0 - draw a point
	*/
	if (rad == 0) {
		return (pixelRGBA(renderer, x, y, r, g, b, a));
	}

	// Octant labelling
	//      
	//  \ 5 | 6 /
	//   \  |  /
	//  4 \ | / 7
	//     \|/
	//------+------ +x
	//     /|\
			//  3 / | \ 0
//   /  |  \
	//  / 2 | 1 \
	//      +y

// Initially reset bitmask to 0x00000000
// the set whether or not to keep drawing a given octant.
// For example: 0x00111100 means we're drawing in octants 2-5
	drawoct = 0;

	/*
	* Fixup angles
	*/
	start %= 360;
	end %= 360;
	// 0 <= start & end < 360; note that sometimes start > end - if so, arc goes back through 0.
	while (start < 0) start += 360;
	while (end < 0) end += 360;
	start %= 360;
	end %= 360;

	// now, we find which octants we're drawing in.
	startoct = start / 45;
	endoct = end / 45;
	oct = startoct - 1; // we increment as first step in loop

						// stopval_start, stopval_end; 
						// what values of cx to stop at.
	do {
		oct = (oct + 1) % 8;

		if (oct == startoct) {
			// need to compute stopval_start for this octant.  Look at picture above if this is unclear
			dstart = (double)start;
			switch (oct)
			{
			case 0:
			case 3:
				temp = sin(dstart * M_PI / 180.);
				break;
			case 1:
			case 6:
				temp = cos(dstart * M_PI / 180.);
				break;
			case 2:
			case 5:
				temp = -cos(dstart * M_PI / 180.);
				break;
			case 4:
			case 7:
				temp = -sin(dstart * M_PI / 180.);
				break;
			}
			temp *= rad;
			stopval_start = (int)temp; // always round down

									   // This isn't arbitrary, but requires graph paper to explain well.
									   // The basic idea is that we're always changing drawoct after we draw, so we
									   // stop immediately after we render the last sensible pixel at x = ((int)temp).

									   // and whether to draw in this octant initially
			if (oct % 2) drawoct |= (1 << oct); // this is basically like saying drawoct[oct] = true, if drawoct were a bool array
			else		 drawoct &= 255 - (1 << oct); // this is basically like saying drawoct[oct] = false
		}
		if (oct == endoct) {
			// need to compute stopval_end for this octant
			dend = (double)end;
			switch (oct)
			{
			case 0:
			case 3:
				temp = sin(dend * M_PI / 180);
				break;
			case 1:
			case 6:
				temp = cos(dend * M_PI / 180);
				break;
			case 2:
			case 5:
				temp = -cos(dend * M_PI / 180);
				break;
			case 4:
			case 7:
				temp = -sin(dend * M_PI / 180);
				break;
			}
			temp *= rad;
			stopval_end = (int)temp;

			// and whether to draw in this octant initially
			if (startoct == endoct) {
				// note:      we start drawing, stop, then start again in this case
				// otherwise: we only draw in this octant, so initialize it to false, it will get set back to true
				if (start > end) {
					// unfortunately, if we're in the same octant and need to draw over the whole circle, 
					// we need to set the rest to true, because the while loop will end at the bottom.
					drawoct = 255;
				}
				else {
					drawoct &= 255 - (1 << oct);
				}
			}
			else if (oct % 2) drawoct &= 255 - (1 << oct);
			else			  drawoct |= (1 << oct);
		}
		else if (oct != startoct) { // already verified that it's != endoct
			drawoct |= (1 << oct); // draw this entire segment
		}
	} while (oct != endoct);

	// so now we have what octants to draw and when to draw them. all that's left is the actual raster code.

	/*
	* Set color
	*/
	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

	/*
	* Draw arc
	*/
	do {
		ypcy = y + cy;
		ymcy = y - cy;
		if (cx > 0) {
			xpcx = x + cx;
			xmcx = x - cx;

			// always check if we're drawing a certain octant before adding a pixel to that octant.
			if (drawoct & 4)  result |= SDL_RenderDrawPoint(renderer, xmcx, ypcy);
			if (drawoct & 2)  result |= SDL_RenderDrawPoint(renderer, xpcx, ypcy);
			if (drawoct & 32) result |= SDL_RenderDrawPoint(renderer, xmcx, ymcy);
			if (drawoct & 64) result |= SDL_RenderDrawPoint(renderer, xpcx, ymcy);
		}
		else {
			if (drawoct & 96) result |= SDL_RenderDrawPoint(renderer, x, ymcy);
			if (drawoct & 6)  result |= SDL_RenderDrawPoint(renderer, x, ypcy);
		}

		xpcy = x + cy;
		xmcy = x - cy;
		if (cx > 0 && cx != cy) {
			ypcx = y + cx;
			ymcx = y - cx;
			if (drawoct & 8)   result |= SDL_RenderDrawPoint(renderer, xmcy, ypcx);
			if (drawoct & 1)   result |= SDL_RenderDrawPoint(renderer, xpcy, ypcx);
			if (drawoct & 16)  result |= SDL_RenderDrawPoint(renderer, xmcy, ymcx);
			if (drawoct & 128) result |= SDL_RenderDrawPoint(renderer, xpcy, ymcx);
		}
		else if (cx == 0) {
			if (drawoct & 24)  result |= SDL_RenderDrawPoint(renderer, xmcy, y);
			if (drawoct & 129) result |= SDL_RenderDrawPoint(renderer, xpcy, y);
		}

		/*
		* Update whether we're drawing an octant
		*/
		if (stopval_start == cx) {
			// works like an on-off switch.  
			// This is just in case start & end are in the same octant.
			if (drawoct & (1 << startoct)) drawoct &= 255 - (1 << startoct);
			else						   drawoct |= (1 << startoct);
		}
		if (stopval_end == cx) {
			if (drawoct & (1 << endoct)) drawoct &= 255 - (1 << endoct);
			else						 drawoct |= (1 << endoct);
		}

		/*
		* Update pixels
		*/
		if (df < 0) {
			df += d_e;
			d_e += 2;
			d_se += 2;
		}
		else {
			df += d_se;
			d_e += 2;
			d_se += 4;
			cy--;
		}
		cx++;
	} while (cx <= cy);

	return (result);
}

/* ----- AA Circle */

/*!
\brief Draw anti-aliased circle with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the aa-circle.
\param y Y coordinate of the center of the aa-circle.
\param rad Radius in pixels of the aa-circle.
\param r The red value of the aa-circle to draw.
\param g The green value of the aa-circle to draw.
\param b The blue value of the aa-circle to draw.
\param a The alpha value of the aa-circle to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::aacircleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw
	*/
	return aaellipseRGBA(renderer, x, y, rad, rad, r, g, b, a);
}

/* ----- Filled Circle */

/*!
\brief Draw filled circle with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the filled circle.
\param y Y coordinate of the center of the filled circle.
\param rad Radius in pixels of the filled circle.
\param r The red value of the filled circle to draw.
\param g The green value of the filled circle to draw.
\param b The blue value of the filled circle to draw.
\param a The alpha value of the filled circle to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::filledCircleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	Sint16 cx = 0;
	Sint16 cy = rad;
	Sint16 ocx = (Sint16)0xffff;
	Sint16 ocy = (Sint16)0xffff;
	Sint16 df = 1 - rad;
	Sint16 d_e = 3;
	Sint16 d_se = -2 * rad + 5;
	Sint16 xpcx, xmcx, xpcy, xmcy;
	Sint16 ypcy, ymcy, ypcx, ymcx;

	/*
	* Sanity check radius
	*/
	if (rad < 0) {
		return (-1);
	}

	/*
	* Special case for rad=0 - draw a point
	*/
	if (rad == 0) {
		return (pixelRGBA(renderer, x, y, r, g, b, a));
	}

	/*
	* Set color
	*/
	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

	/*
	* Draw
	*/
	do {
		xpcx = x + cx;
		xmcx = x - cx;
		xpcy = x + cy;
		xmcy = x - cy;
		if (ocy != cy) {
			if (cy > 0) {
				ypcy = y + cy;
				ymcy = y - cy;
				result |= hline(renderer, xmcx, xpcx, ypcy);
				result |= hline(renderer, xmcx, xpcx, ymcy);
			}
			else {
				result |= hline(renderer, xmcx, xpcx, y);
			}
			ocy = cy;
		}
		if (ocx != cx) {
			if (cx != cy) {
				if (cx > 0) {
					ypcx = y + cx;
					ymcx = y - cx;
					result |= hline(renderer, xmcy, xpcy, ymcx);
					result |= hline(renderer, xmcy, xpcy, ypcx);
				}
				else {
					result |= hline(renderer, xmcy, xpcy, y);
				}
			}
			ocx = cx;
		}

		/*
		* Update
		*/
		if (df < 0) {
			df += d_e;
			d_e += 2;
			d_se += 2;
		}
		else {
			df += d_se;
			d_e += 2;
			d_se += 4;
			cy--;
		}
		cx++;
	} while (cx <= cy);

	return (result);
}

/* ----- Ellipse */

/*!
\brief Draw ellipse with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the ellipse.
\param y Y coordinate of the center of the ellipse.
\param rx Horizontal radius in pixels of the ellipse.
\param ry Vertical radius in pixels of the ellipse.
\param r The red value of the ellipse to draw.
\param g The green value of the ellipse to draw.
\param b The blue value of the ellipse to draw.
\param a The alpha value of the ellipse to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::ellipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	int ix, iy;
	int h, i, j, k;
	int oh, oi, oj, ok;
	int xmh, xph, ypk, ymk;
	int xmi, xpi, ymj, ypj;
	int xmj, xpj, ymi, ypi;
	int xmk, xpk, ymh, yph;

	/*
	* Sanity check radii
	*/
	if ((rx < 0) || (ry < 0)) {
		return (-1);
	}

	/*
	* Special case for rx=0 - draw a vline
	*/
	if (rx == 0) {
		return (vlineRGBA(renderer, x, y - ry, y + ry, r, g, b, a));
	}
	/*
	* Special case for ry=0 - draw a hline
	*/
	if (ry == 0) {
		return (hlineRGBA(renderer, x - rx, x + rx, y, r, g, b, a));
	}

	/*
	* Set color
	*/
	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

	/*
	* Init vars
	*/
	oh = oi = oj = ok = 0xFFFF;

	/*
	* Draw
	*/
	if (rx > ry) {
		ix = 0;
		iy = rx * 64;

		do {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * ry) / rx;
			k = (i * ry) / rx;

			if (((ok != k) && (oj != k)) || ((oj != j) && (ok != j)) || (k != j)) {
				xph = x + h;
				xmh = x - h;
				if (k > 0) {
					ypk = y + k;
					ymk = y - k;
					result |= SDL_RenderDrawPoint(renderer, xmh, ypk);
					result |= SDL_RenderDrawPoint(renderer, xph, ypk);
					result |= SDL_RenderDrawPoint(renderer, xmh, ymk);
					result |= SDL_RenderDrawPoint(renderer, xph, ymk);
				}
				else {
					result |= SDL_RenderDrawPoint(renderer, xmh, y);
					result |= SDL_RenderDrawPoint(renderer, xph, y);
				}
				ok = k;
				xpi = x + i;
				xmi = x - i;
				if (j > 0) {
					ypj = y + j;
					ymj = y - j;
					result |= SDL_RenderDrawPoint(renderer, xmi, ypj);
					result |= SDL_RenderDrawPoint(renderer, xpi, ypj);
					result |= SDL_RenderDrawPoint(renderer, xmi, ymj);
					result |= SDL_RenderDrawPoint(renderer, xpi, ymj);
				}
				else {
					result |= SDL_RenderDrawPoint(renderer, xmi, y);
					result |= SDL_RenderDrawPoint(renderer, xpi, y);
				}
				oj = j;
			}

			ix = ix + iy / rx;
			iy = iy - ix / rx;

		} while (i > h);
	}
	else {
		ix = 0;
		iy = ry * 64;

		do {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * rx) / ry;
			k = (i * rx) / ry;

			if (((oi != i) && (oh != i)) || ((oh != h) && (oi != h) && (i != h))) {
				xmj = x - j;
				xpj = x + j;
				if (i > 0) {
					ypi = y + i;
					ymi = y - i;
					result |= SDL_RenderDrawPoint(renderer, xmj, ypi);
					result |= SDL_RenderDrawPoint(renderer, xpj, ypi);
					result |= SDL_RenderDrawPoint(renderer, xmj, ymi);
					result |= SDL_RenderDrawPoint(renderer, xpj, ymi);
				}
				else {
					result |= SDL_RenderDrawPoint(renderer, xmj, y);
					result |= SDL_RenderDrawPoint(renderer, xpj, y);
				}
				oi = i;
				xmk = x - k;
				xpk = x + k;
				if (h > 0) {
					yph = y + h;
					ymh = y - h;
					result |= SDL_RenderDrawPoint(renderer, xmk, yph);
					result |= SDL_RenderDrawPoint(renderer, xpk, yph);
					result |= SDL_RenderDrawPoint(renderer, xmk, ymh);
					result |= SDL_RenderDrawPoint(renderer, xpk, ymh);
				}
				else {
					result |= SDL_RenderDrawPoint(renderer, xmk, y);
					result |= SDL_RenderDrawPoint(renderer, xpk, y);
				}
				oh = h;
			}

			ix = ix + iy / ry;
			iy = iy - ix / ry;

		} while (i > h);
	}

	return (result);
}

/* ----- AA Ellipse */

/* Windows targets do not have lrint, so provide a local inline version */
#if defined(_MSC_VER)
/* Detect 64bit and use intrinsic version */
#ifdef _M_X64
#include <emmintrin.h>
static __inline long
lrint(float f)
{
	return _mm_cvtss_si32(_mm_load_ss(&f));
}
#elif defined(_M_IX86)
__inline long int
lrint(double flt)
{
	int intgr;
	_asm
	{
		fld flt
		fistp intgr
	};
	return intgr;
}
#elif defined(_M_ARM)
#include <armintr.h>
#pragma warning(push)
#pragma warning(disable: 4716)
__declspec(naked) long int
lrint(double flt)
{
	__emit(0xEC410B10); // fmdrr  d0, r0, r1
	__emit(0xEEBD0B40); // ftosid s0, d0
	__emit(0xEE100A10); // fmrs   r0, s0
	__emit(0xE12FFF1E); // bx     lr
}
#pragma warning(pop)
#else
#error lrint needed for MSVC on non X86/AMD64/ARM targets.
#endif
#endif

/*!
\brief Draw anti-aliased ellipse with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the aa-ellipse.
\param y Y coordinate of the center of the aa-ellipse.
\param rx Horizontal radius in pixels of the aa-ellipse.
\param ry Vertical radius in pixels of the aa-ellipse.
\param r The red value of the aa-ellipse to draw.
\param g The green value of the aa-ellipse to draw.
\param b The blue value of the aa-ellipse to draw.
\param a The alpha value of the aa-ellipse to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::aaellipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	int i;
	int a2, b2, ds, dt, dxt, t, s, d;
	Sint16 xp, yp, xs, ys, dyt, od, xx, yy, xc2, yc2;
	float cp;
	double sab;
	Uint8 weight, iweight;

	/*
	* Sanity check radii
	*/
	if ((rx < 0) || (ry < 0)) {
		return (-1);
	}

	/*
	* Special case for rx=0 - draw a vline
	*/
	if (rx == 0) {
		return (vlineRGBA(renderer, x, y - ry, y + ry, r, g, b, a));
	}
	/*
	* Special case for ry=0 - draw an hline
	*/
	if (ry == 0) {
		return (hlineRGBA(renderer, x - rx, x + rx, y, r, g, b, a));
	}

	/* Variable setup */
	a2 = rx * rx;
	b2 = ry * ry;

	ds = 2 * a2;
	dt = 2 * b2;

	xc2 = 2 * x;
	yc2 = 2 * y;

	sab = sqrt((double)(a2 + b2));
	od = (Sint16)lrint(sab*0.01) + 1; /* introduce some overdraw */
	dxt = (Sint16)lrint((double)a2 / sab) + od;

	t = 0;
	s = -2 * a2 * ry;
	d = 0;

	xp = x;
	yp = y - ry;

	/* Draw */
	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);

	/* "End points" */
	result |= pixelRGBA(renderer, xp, yp, r, g, b, a);
	result |= pixelRGBA(renderer, xc2 - xp, yp, r, g, b, a);
	result |= pixelRGBA(renderer, xp, yc2 - yp, r, g, b, a);
	result |= pixelRGBA(renderer, xc2 - xp, yc2 - yp, r, g, b, a);

	for (i = 1; i <= dxt; i++) {
		xp--;
		d += t - b2;

		if (d >= 0)
			ys = yp - 1;
		else if ((d - s - a2) > 0) {
			if ((2 * d - s - a2) >= 0)
				ys = yp + 1;
			else {
				ys = yp;
				yp++;
				d -= s + a2;
				s += ds;
			}
		}
		else {
			yp++;
			ys = yp + 1;
			d -= s + a2;
			s += ds;
		}

		t -= dt;

		/* Calculate alpha */
		if (s != 0) {
			cp = (float)abs(d) / (float)abs(s);
			if (cp > 1.0) {
				cp = 1.0;
			}
		}
		else {
			cp = 1.0;
		}

		/* Calculate weights */
		weight = (Uint8)(cp * 255);
		iweight = 255 - weight;

		/* Upper half */
		xx = xc2 - xp;
		result |= pixelRGBAWeight(renderer, xp, yp, r, g, b, a, iweight);
		result |= pixelRGBAWeight(renderer, xx, yp, r, g, b, a, iweight);

		result |= pixelRGBAWeight(renderer, xp, ys, r, g, b, a, weight);
		result |= pixelRGBAWeight(renderer, xx, ys, r, g, b, a, weight);

		/* Lower half */
		yy = yc2 - yp;
		result |= pixelRGBAWeight(renderer, xp, yy, r, g, b, a, iweight);
		result |= pixelRGBAWeight(renderer, xx, yy, r, g, b, a, iweight);

		yy = yc2 - ys;
		result |= pixelRGBAWeight(renderer, xp, yy, r, g, b, a, weight);
		result |= pixelRGBAWeight(renderer, xx, yy, r, g, b, a, weight);
	}

	/* Replaces original approximation code dyt = abs(yp - yc); */
	dyt = (Sint16)lrint((double)b2 / sab) + od;

	for (i = 1; i <= dyt; i++) {
		yp++;
		d -= s + a2;

		if (d <= 0)
			xs = xp + 1;
		else if ((d + t - b2) < 0) {
			if ((2 * d + t - b2) <= 0)
				xs = xp - 1;
			else {
				xs = xp;
				xp--;
				d += t - b2;
				t -= dt;
			}
		}
		else {
			xp--;
			xs = xp - 1;
			d += t - b2;
			t -= dt;
		}

		s += ds;

		/* Calculate alpha */
		if (t != 0) {
			cp = (float)abs(d) / (float)abs(t);
			if (cp > 1.0) {
				cp = 1.0;
			}
		}
		else {
			cp = 1.0;
		}

		/* Calculate weight */
		weight = (Uint8)(cp * 255);
		iweight = 255 - weight;

		/* Left half */
		xx = xc2 - xp;
		yy = yc2 - yp;
		result |= pixelRGBAWeight(renderer, xp, yp, r, g, b, a, iweight);
		result |= pixelRGBAWeight(renderer, xx, yp, r, g, b, a, iweight);

		result |= pixelRGBAWeight(renderer, xp, yy, r, g, b, a, iweight);
		result |= pixelRGBAWeight(renderer, xx, yy, r, g, b, a, iweight);

		/* Right half */
		xx = xc2 - xs;
		result |= pixelRGBAWeight(renderer, xs, yp, r, g, b, a, weight);
		result |= pixelRGBAWeight(renderer, xx, yp, r, g, b, a, weight);

		result |= pixelRGBAWeight(renderer, xs, yy, r, g, b, a, weight);
		result |= pixelRGBAWeight(renderer, xx, yy, r, g, b, a, weight);
	}

	return (result);
}

/* ---- Filled Ellipse */

/*!
\brief Draw filled ellipse with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the filled ellipse.
\param y Y coordinate of the center of the filled ellipse.
\param rx Horizontal radius in pixels of the filled ellipse.
\param ry Vertical radius in pixels of the filled ellipse.
\param r The red value of the filled ellipse to draw.
\param g The green value of the filled ellipse to draw.
\param b The blue value of the filled ellipse to draw.
\param a The alpha value of the filled ellipse to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::filledEllipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	int ix, iy;
	int h, i, j, k;
	int oh, oi, oj, ok;
	int xmh, xph;
	int xmi, xpi;
	int xmj, xpj;
	int xmk, xpk;

	/*
	* Sanity check radii
	*/
	if ((rx < 0) || (ry < 0)) {
		return (-1);
	}

	/*
	* Special case for rx=0 - draw a vline
	*/
	if (rx == 0) {
		return (vlineRGBA(renderer, x, y - ry, y + ry, r, g, b, a));
	}
	/*
	* Special case for ry=0 - draw a hline
	*/
	if (ry == 0) {
		return (hlineRGBA(renderer, x - rx, x + rx, y, r, g, b, a));
	}

	/*
	* Set color
	*/
	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

	/*
	* Init vars
	*/
	oh = oi = oj = ok = 0xFFFF;

	/*
	* Draw
	*/
	if (rx > ry) {
		ix = 0;
		iy = rx * 64;

		do {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * ry) / rx;
			k = (i * ry) / rx;

			if ((ok != k) && (oj != k)) {
				xph = x + h;
				xmh = x - h;
				if (k > 0) {
					result |= hline(renderer, xmh, xph, y + k);
					result |= hline(renderer, xmh, xph, y - k);
				}
				else {
					result |= hline(renderer, xmh, xph, y);
				}
				ok = k;
			}
			if ((oj != j) && (ok != j) && (k != j)) {
				xmi = x - i;
				xpi = x + i;
				if (j > 0) {
					result |= hline(renderer, xmi, xpi, y + j);
					result |= hline(renderer, xmi, xpi, y - j);
				}
				else {
					result |= hline(renderer, xmi, xpi, y);
				}
				oj = j;
			}

			ix = ix + iy / rx;
			iy = iy - ix / rx;

		} while (i > h);
	}
	else {
		ix = 0;
		iy = ry * 64;

		do {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * rx) / ry;
			k = (i * rx) / ry;

			if ((oi != i) && (oh != i)) {
				xmj = x - j;
				xpj = x + j;
				if (i > 0) {
					result |= hline(renderer, xmj, xpj, y + i);
					result |= hline(renderer, xmj, xpj, y - i);
				}
				else {
					result |= hline(renderer, xmj, xpj, y);
				}
				oi = i;
			}
			if ((oh != h) && (oi != h) && (i != h)) {
				xmk = x - k;
				xpk = x + k;
				if (h > 0) {
					result |= hline(renderer, xmk, xpk, y + h);
					result |= hline(renderer, xmk, xpk, y - h);
				}
				else {
					result |= hline(renderer, xmk, xpk, y);
				}
				oh = h;
			}

			ix = ix + iy / ry;
			iy = iy - ix / ry;

		} while (i > h);
	}

	return (result);
}

/* ----- Pie */

/*!
\brief Internal float (low-speed) pie-calc implementation by drawing polygons.

Note: Determines vertex array and uses polygon or filledPolygon drawing routines to render.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the pie.
\param y Y coordinate of the center of the pie.
\param rad Radius in pixels of the pie.
\param start Starting radius in degrees of the pie.
\param end Ending radius in degrees of the pie.
\param r The red value of the pie to draw.
\param g The green value of the pie to draw.
\param b The blue value of the pie to draw.
\param a The alpha value of the pie to draw.
\param filled Flag indicating if the pie should be filled (=1) or not (=0).

\returns Returns 0 on success, -1 on failure.
*/
/* TODO: rewrite algorithm; pie is not always accurate */
int GerenciadorDeGraficos::_pieRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 filled)
{
	int result;
	double angle, start_angle, end_angle;
	double deltaAngle;
	double dr;
	int numpoints, i;
	Sint16 *vx, *vy;

	/*
	* Sanity check radii
	*/
	if (rad < 0) {
		return (-1);
	}

	/*
	* Fixup angles
	*/
	start = start % 360;
	end = end % 360;

	/*
	* Special case for rad=0 - draw a point
	*/
	if (rad == 0) {
		return (pixelRGBA(renderer, x, y, r, g, b, a));
	}

	/*
	* Variable setup
	*/
	dr = (double)rad;
	deltaAngle = 3.0 / dr;
	start_angle = (double)start *(2.0 * M_PI / 360.0);
	end_angle = (double)end *(2.0 * M_PI / 360.0);
	if (start > end) {
		end_angle += (2.0 * M_PI);
	}

	/* We will always have at least 2 points */
	numpoints = 2;

	/* Count points (rather than calculating it) */
	angle = start_angle;
	while (angle < end_angle) {
		angle += deltaAngle;
		numpoints++;
	}

	/* Allocate combined vertex array */
	vx = vy = (Sint16 *)malloc(2 * sizeof(Uint16) * numpoints);
	if (vx == NULL) {
		return (-1);
	}

	/* Update point to start of vy */
	vy += numpoints;

	/* Center */
	vx[0] = x;
	vy[0] = y;

	/* First vertex */
	angle = start_angle;
	vx[1] = x + (int)(dr * cos(angle));
	vy[1] = y + (int)(dr * sin(angle));

	if (numpoints<3)
	{
		result = lineRGBA(renderer, vx[0], vy[0], vx[1], vy[1], r, g, b, a);
	}
	else
	{
		/* Calculate other vertices */
		i = 2;
		angle = start_angle;
		while (angle < end_angle) {
			angle += deltaAngle;
			if (angle>end_angle)
			{
				angle = end_angle;
			}
			vx[i] = x + (int)(dr * cos(angle));
			vy[i] = y + (int)(dr * sin(angle));
			i++;
		}

		/* Draw */
		if (filled) {
			result = filledPolygonRGBA(renderer, vx, vy, numpoints, r, g, b, a);
		}
		else {
			result = polygonRGBA(renderer, vx, vy, numpoints, r, g, b, a);
		}
	}

	/* Free combined vertex array */
	free(vx);

	return (result);
}

/* ------ Trigon */

/*!
\brief Draw trigon (triangle outline) with alpha blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the trigon.
\param y1 Y coordinate of the first point of the trigon.
\param x2 X coordinate of the second point of the trigon.
\param y2 Y coordinate of the second point of the trigon.
\param x3 X coordinate of the third point of the trigon.
\param y3 Y coordinate of the third point of the trigon.
\param r The red value of the trigon to draw.
\param g The green value of the trigon to draw.
\param b The blue value of the trigon to draw.
\param a The alpha value of the trigon to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::trigonRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3,
	Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Sint16 vx[3];
	Sint16 vy[3];

	vx[0] = x1;
	vx[1] = x2;
	vx[2] = x3;
	vy[0] = y1;
	vy[1] = y2;
	vy[2] = y3;

	return(polygonRGBA(renderer, vx, vy, 3, r, g, b, a));
}

/* ------ AA-Trigon */

/*!
\brief Draw anti-aliased trigon (triangle outline) with alpha blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the aa-trigon.
\param y1 Y coordinate of the first point of the aa-trigon.
\param x2 X coordinate of the second point of the aa-trigon.
\param y2 Y coordinate of the second point of the aa-trigon.
\param x3 X coordinate of the third point of the aa-trigon.
\param y3 Y coordinate of the third point of the aa-trigon.
\param r The red value of the aa-trigon to draw.
\param g The green value of the aa-trigon to draw.
\param b The blue value of the aa-trigon to draw.
\param a The alpha value of the aa-trigon to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::aatrigonRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3,
	Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Sint16 vx[3];
	Sint16 vy[3];

	vx[0] = x1;
	vx[1] = x2;
	vx[2] = x3;
	vy[0] = y1;
	vy[1] = y2;
	vy[2] = y3;

	return(aapolygonRGBA(renderer, vx, vy, 3, r, g, b, a));
}

/* ------ Filled Trigon */

/*!
\brief Draw filled trigon (triangle) with alpha blending.

Note: Creates vertex array and uses aapolygon routine to render.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the filled trigon.
\param y1 Y coordinate of the first point of the filled trigon.
\param x2 X coordinate of the second point of the filled trigon.
\param y2 Y coordinate of the second point of the filled trigon.
\param x3 X coordinate of the third point of the filled trigon.
\param y3 Y coordinate of the third point of the filled trigon.
\param r The red value of the filled trigon to draw.
\param g The green value of the filled trigon to draw.
\param b The blue value of the filled trigon to draw.
\param a The alpha value of the filled trigon to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::filledTrigonRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3,
	Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Sint16 vx[3];
	Sint16 vy[3];

	vx[0] = x1;
	vx[1] = x2;
	vx[2] = x3;
	vy[0] = y1;
	vy[1] = y2;
	vy[2] = y3;

	return(filledPolygonRGBA(renderer, vx, vy, 3, r, g, b, a));
}

/* ---- Polygon */

/*!
\brief Draw polygon with the currently set color and blend mode.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the polygon.
\param vy Vertex array containing Y coordinates of the points of the polygon.
\param n Number of points in the vertex array. Minimum number is 3.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::polygon(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n)
{
	/*
	* Draw
	*/
	int result = 0;
	int i, nn;
	SDL_Point* points;

	/*
	* Vertex array NULL check
	*/
	if (vx == NULL) {
		return (-1);
	}
	if (vy == NULL) {
		return (-1);
	}

	/*
	* Sanity check
	*/
	if (n < 3) {
		return (-1);
	}

	/*
	* Create array of points
	*/
	nn = n + 1;
	points = (SDL_Point*)malloc(sizeof(SDL_Point) * nn);
	if (points == NULL)
	{
		return -1;
	}
	for (i = 0; i<n; i++)
	{
		points[i].x = vx[i];
		points[i].y = vy[i];
	}
	points[n].x = vx[0];
	points[n].y = vy[0];

	/*
	* Draw
	*/
	result |= SDL_RenderDrawLines(renderer, points, nn);
	free(points);

	return (result);
}

/*!
\brief Draw polygon with alpha blending.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the polygon.
\param vy Vertex array containing Y coordinates of the points of the polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param r The red value of the polygon to draw.
\param g The green value of the polygon to draw.
\param b The blue value of the polygon to draw.
\param a The alpha value of the polygon to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::polygonRGBA(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw
	*/
	int result;
	const Sint16 *x1, *y1, *x2, *y2;

	/*
	* Vertex array NULL check
	*/
	if (vx == NULL) {
		return (-1);
	}
	if (vy == NULL) {
		return (-1);
	}

	/*
	* Sanity check
	*/
	if (n < 3) {
		return (-1);
	}

	/*
	* Pointer setup
	*/
	x1 = x2 = vx;
	y1 = y2 = vy;
	x2++;
	y2++;

	/*
	* Set color
	*/
	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

	/*
	* Draw
	*/
	result |= polygon(renderer, vx, vy, n);

	return (result);
}

/* ---- AA-Polygon */

/*!
\brief Draw anti-aliased polygon with alpha blending.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the aa-polygon.
\param vy Vertex array containing Y coordinates of the points of the aa-polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param r The red value of the aa-polygon to draw.
\param g The green value of the aa-polygon to draw.
\param b The blue value of the aa-polygon to draw.
\param a The alpha value of the aa-polygon to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::aapolygonRGBA(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	int i;
	const Sint16 *x1, *y1, *x2, *y2;

	/*
	* Vertex array NULL check
	*/
	if (vx == NULL) {
		return (-1);
	}
	if (vy == NULL) {
		return (-1);
	}

	/*
	* Sanity check
	*/
	if (n < 3) {
		return (-1);
	}

	/*
	* Pointer setup
	*/
	x1 = x2 = vx;
	y1 = y2 = vy;
	x2++;
	y2++;

	/*
	* Draw
	*/
	result = 0;
	for (i = 1; i < n; i++) {
		result |= _aalineRGBA(renderer, *x1, *y1, *x2, *y2, r, g, b, a, 0);
		x1 = x2;
		y1 = y2;
		x2++;
		y2++;
	}

	result |= _aalineRGBA(renderer, *x1, *y1, *vx, *vy, r, g, b, a, 0);

	return (result);
}

/* ---- Filled Polygon */

/*!
\brief Internal helper qsort callback functions used in filled polygon drawing.

\param a The surface to draw on.
\param b Vertex array containing X coordinates of the points of the polygon.

\returns Returns 0 if a==b, a negative number if a<b or a positive number if a>b.
*/
int GerenciadorDeGraficos::_gfxPrimitivesCompareInt(const void *a, const void *b)
{
	return (*(const int *)a) - (*(const int *)b);
}

/*!
\brief Global vertex array to use if optional parameters are not given in filledPolygonMT calls.

Note: Used for non-multithreaded (default) operation of filledPolygonMT.
*/
int *GerenciadorDeGraficos::gfxPrimitivesPolyIntsGlobal = NULL;

/*!
\brief Flag indicating if global vertex array was already allocated.

Note: Used for non-multithreaded (default) operation of filledPolygonMT.
*/
int GerenciadorDeGraficos::gfxPrimitivesPolyAllocatedGlobal = 0;

/*!
\brief Draw filled polygon with alpha blending (multi-threaded capable).

Note: The last two parameters are optional; but are required for multithreaded operation.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the filled polygon.
\param vy Vertex array containing Y coordinates of the points of the filled polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param r The red value of the filled polygon to draw.
\param g The green value of the filled polygon to draw.
\param b The blue value of the filled polygon to draw.
\param a The alpha value of the filled polygon to draw.
\param polyInts Preallocated, temporary vertex array used for sorting vertices. Required for multithreaded operation; set to NULL otherwise.
\param polyAllocated Flag indicating if temporary vertex array was allocated. Required for multithreaded operation; set to NULL otherwise.

\returns Returns 0 on success, -1 on failure.
*/
#include <stdlib.h>
int GerenciadorDeGraficos::filledPolygonRGBAMT(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int **polyInts, int *polyAllocated)
{
	int result;
	int i;
	int y, xa, xb;
	int miny, maxy;
	int x1, y1;
	int x2, y2;
	int ind1, ind2;
	int ints;
	int *gfxPrimitivesPolyInts = NULL;
	int *gfxPrimitivesPolyIntsNew = NULL;
	int gfxPrimitivesPolyAllocated = 0;

	/*
	* Vertex array NULL check
	*/
	if (vx == NULL) {
		return (-1);
	}
	if (vy == NULL) {
		return (-1);
	}

	/*
	* Sanity check number of edges
	*/
	if (n < 3) {
		return -1;
	}

	/*
	* Map polygon cache
	*/
	if ((polyInts == NULL) || (polyAllocated == NULL)) {
		/* Use global cache */
		gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsGlobal;
		gfxPrimitivesPolyAllocated = gfxPrimitivesPolyAllocatedGlobal;
	}
	else {
		/* Use local cache */
		gfxPrimitivesPolyInts = *polyInts;
		gfxPrimitivesPolyAllocated = *polyAllocated;
	}

	/*
	* Allocate temp array, only grow array
	*/
	if (!gfxPrimitivesPolyAllocated) {
		gfxPrimitivesPolyInts = (int *)malloc(sizeof(int) * n);
		gfxPrimitivesPolyAllocated = n;
	}
	else {
		if (gfxPrimitivesPolyAllocated < n) {
			gfxPrimitivesPolyIntsNew = (int *)realloc(gfxPrimitivesPolyInts, sizeof(int) * n);
			if (!gfxPrimitivesPolyIntsNew) {
				if (!gfxPrimitivesPolyInts) {
					free(gfxPrimitivesPolyInts);
					gfxPrimitivesPolyInts = NULL;
				}
				gfxPrimitivesPolyAllocated = 0;
			}
			else {
				gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsNew;
				gfxPrimitivesPolyAllocated = n;
			}
		}
	}

	/*
	* Check temp array
	*/
	if (gfxPrimitivesPolyInts == NULL) {
		gfxPrimitivesPolyAllocated = 0;
	}

	/*
	* Update cache variables
	*/
	if ((polyInts == NULL) || (polyAllocated == NULL)) {
		gfxPrimitivesPolyIntsGlobal = gfxPrimitivesPolyInts;
		gfxPrimitivesPolyAllocatedGlobal = gfxPrimitivesPolyAllocated;
	}
	else {
		*polyInts = gfxPrimitivesPolyInts;
		*polyAllocated = gfxPrimitivesPolyAllocated;
	}

	/*
	* Check temp array again
	*/
	if (gfxPrimitivesPolyInts == NULL) {
		return(-1);
	}

	/*
	* Determine Y maxima
	*/
	miny = vy[0];
	maxy = vy[0];
	for (i = 1; (i < n); i++) {
		if (vy[i] < miny) {
			miny = vy[i];
		}
		else if (vy[i] > maxy) {
			maxy = vy[i];
		}
	}

	/*
	* Draw, scanning y
	*/
	result = 0;
	for (y = miny; (y <= maxy); y++) {
		ints = 0;
		for (i = 0; (i < n); i++) {
			if (!i) {
				ind1 = n - 1;
				ind2 = 0;
			}
			else {
				ind1 = i - 1;
				ind2 = i;
			}
			y1 = vy[ind1];
			y2 = vy[ind2];
			if (y1 < y2) {
				x1 = vx[ind1];
				x2 = vx[ind2];
			}
			else if (y1 > y2) {
				y2 = vy[ind1];
				y1 = vy[ind2];
				x2 = vx[ind1];
				x1 = vx[ind2];
			}
			else {
				continue;
			}
			if (((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2))) {
				gfxPrimitivesPolyInts[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
			}
		}

		qsort(gfxPrimitivesPolyInts, ints, sizeof(int), _gfxPrimitivesCompareInt);

		/*
		* Set color
		*/
		result = 0;
		result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
		result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

		for (i = 0; (i < ints); i += 2) {
			xa = gfxPrimitivesPolyInts[i] + 1;
			xa = (xa >> 16) + ((xa & 32768) >> 15);
			xb = gfxPrimitivesPolyInts[i + 1] - 1;
			xb = (xb >> 16) + ((xb & 32768) >> 15);
			result |= hline(renderer, xa, xb, y);
		}
	}

	return (result);
}

/*!
\brief Draw filled polygon with alpha blending.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the filled polygon.
\param vy Vertex array containing Y coordinates of the points of the filled polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param r The red value of the filled polygon to draw.
\param g The green value of the filled polygon to draw.
\param b The blue value of the filed polygon to draw.
\param a The alpha value of the filled polygon to draw.

\returns Returns 0 on success, -1 on failure.
*/
int GerenciadorDeGraficos::filledPolygonRGBA(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return filledPolygonRGBAMT(renderer, vx, vy, n, r, g, b, a, NULL, NULL);
}